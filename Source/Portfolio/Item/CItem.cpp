#include "CItem.h"
#include "Global.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "DataAsset/CItemDataAsset.h"
#include "DataTable/CItemDataTable.h"
#include "Player/CPlayer.h"
#include "Inventory/CInventory.h"

ACItem::ACItem()
{
	CHelpers::CreateSceneComponent(this, &RootGravityComp, "RootGravityComp");
	CheckNull(RootGravityComp);

	CHelpers::CreateSceneComponent(this, &BoxComp, "BoxComp", RootGravityComp);
	CheckNull(BoxComp);

	CHelpers::CreateSceneComponent(this, &MeshComp, "MeshComp", RootComponent);
	CheckNull(MeshComp);

	UStaticMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Lowpoly_Objects_Pack/backpack");
	CheckNull(MeshAsset);

	MeshComp->SetStaticMesh(MeshAsset);

	CHelpers::GetAsset(&DataAsset, "/Game/DataAsset/DA_Item");
	CheckNull(DataAsset);

	CHelpers::GetAsset(&DataTable, "/Game/DataTable/DT_Item"); 	CheckNull(DataTable);

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>("ASC");
	CheckNull(ASC);
}

void ACItem::BeginPlay()
{
	Super::BeginPlay();
	
	if (ASC)
		ASC->InitAbilityActorInfo(this, this);

	if(BoxComp)
		BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACItem::BeginOverlap);

	TArray<FName> DTRowNames = DataTable->GetRowNames();

	int32 Index = FMath::RandRange(0, DTRowNames.Num() - 1);

	Row = *(DataTable->FindRow<FItemDataTable>(DTRowNames[Index], TEXT(""))); }

UAbilitySystemComponent* ACItem::GetAbilitySystemComponent() const
{
	return ASC;
}

void ACItem::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<ACPlayer>())
	{
		ACPlayer* Player = Cast<ACPlayer>(OtherActor);
		CheckNull(Player);
		CheckNull(Player->GetInventory());

		TArray<FName> DTRowNames = DataTable->GetRowNames();

		int32 Index = FMath::RandRange(0, DTRowNames.Num() - 1);

		Player->GetInventory()->AddItemToInventory(*(DataTable->FindRow<FItemDataTable>(DTRowNames[Index], TEXT(""))));

		Destroy();
	}
}


