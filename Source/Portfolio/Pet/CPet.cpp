#include "CPet.h"
#include "Global.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "Components/TextRenderComponent.h"
#include "CPetController.h"
#include "GAS/GA/AI_Attack.h"
#include "GAS/Attribute/CPetAttributeSet.h"
#include "DataAsset/CPetDataAsset.h"

ACPet::ACPet()
{
	PrimaryActorTick.bCanEverTick = true;

	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Assets/BattleWizardPolyart/Meshes/WizardSM");
	CheckNull(MeshAsset);

	GetMesh()->SetSkeletalMesh(MeshAsset);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -80));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	CHelpers::CreateSceneComponent(this, &TextComp, "TextComp", GetMesh());
	CheckNull(TextComp);

	TextComp->SetRelativeLocation(FVector(0, 0, 200));
	TextComp->SetRelativeRotation(FRotator(0, 90, 0));
	TextComp->SetHorizontalAlignment(EHTA_Center);

	CHelpers::GetClass(&AnimClass, "/Game/Pet/ABP_CPet");
	CheckNull(AnimClass);

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>("ASC");
	CheckNull(ASC);

	Attribute = CreateDefaultSubobject<UCPetAttributeSet>("Attribute");
	CheckNull(Attribute);

	CHelpers::GetAsset(&DataAsset, "/Game/DataAsset/DA_Pet");
	CheckNull(DataAsset);
}

void ACPet::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->SetAnimClass(AnimClass);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ACPetController::StaticClass();

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

	ASC->InitAbilityActorInfo(this, this);

	FGameplayAbilitySpec AttackSpec(UAI_Attack::StaticClass());
	ASC->GiveAbility(AttackSpec);

	Attribute->SetBaseHealth(DataAsset->BaseHealth);
	Attribute->SetBaseDamage(DataAsset->BaseDamage);
}

void ACPet::Tick(float DeltaTime)
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

UAbilitySystemComponent* ACPet::GetAbilitySystemComponent() const
{
	return ASC;
}

