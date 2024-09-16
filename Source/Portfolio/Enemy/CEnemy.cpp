#include "CEnemy.h"
#include "Global.h"
#include "AbilitySystemComponent.h"
#include "Components/WidgetComponent.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "Components/TextRenderComponent.h"
#include "DataAsset/CMonsterMeshDataAsset.h"
#include "GAS/Attribute/CMonsterAttributeSet.h"
#include "CEnemyController.h"
#include "GAS/GA/AI_Attack.h"
#include "GAS/GA/AI_GetHit.h"
#include "Widget/CEnemyHealthWidget.h"

ACEnemy::ACEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &TextComp, "TextComp", GetMesh());
	CheckNull(TextComp);

	TextComp->SetRelativeLocation(FVector(0, 0, 200));
	TextComp->SetRelativeRotation(FRotator(0, 90, 0));
	TextComp->SetHorizontalAlignment(EHTA_Center);

	CHelpers::CreateSceneComponent(this, &HealthWidgetComp, "HealthWidgetComp", GetMesh());

	TSubclassOf<UCEnemyHealthWidget> HealthWidgetClass;
	CHelpers::GetClass(&HealthWidgetClass, "/Game/Widget/WB_CEnemyHealthWidget");
	HealthWidgetComp->SetWidgetClass(HealthWidgetClass);
	HealthWidgetComp->SetRelativeLocation(FVector(0, 0, 190));
	HealthWidgetComp->SetDrawSize(FVector2D(120, 20));
	HealthWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>("ASC");
	CheckNull(ASC);

	CHelpers::GetAsset(&DataAsset, "/Game/DataAsset/DA_Monster");
	CheckNull(DataAsset);

	Attribute = CreateDefaultSubobject<UCMonsterAttributeSet>("Attribute");
	CheckNull(Attribute);

}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ACEnemyController::StaticClass();

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

	HealthWidgetComp->InitWidget();
	HealthWidgetObject = Cast<UCEnemyHealthWidget>(HealthWidgetComp->GetUserWidgetObject());
	if (HealthWidgetObject)
		HealthWidgetObject->Update(Attribute->GetCurrentHealth(), Attribute->GetBaseHealth());

	ASC->InitAbilityActorInfo(this, this);

	FGameplayAbilitySpec AttackSpec(UAI_Attack::StaticClass());
	ASC->GiveAbility(AttackSpec);

	FGameplayAbilitySpec HitSpec(UAI_GetHit::StaticClass());
	ASC->GiveAbility(HitSpec);

	TagContainer.AddTag(FGameplayTag::RequestGameplayTag("AI.State.Idle"));

}

void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TagContainer.Num() > 0)
	{
		for (const FGameplayTag& Tag : TagContainer)
		{
			TextComp->SetText(FText::FromString(Tag.ToString()));
		}
	}
}

UAbilitySystemComponent* ACEnemy::GetAbilitySystemComponent() const
{
	return ASC;
}

