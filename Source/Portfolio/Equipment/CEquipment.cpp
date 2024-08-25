#include "CEquipment.h"
#include "Global.h"
#include "GameFramework/Character.h"

ACEquipment::ACEquipment()
{
	PrimaryActorTick.bCanEverTick = true;

	
}

void ACEquipment::BeginPlay()
{
	Super::BeginPlay();

	CheckNull(DataAsset);
	
	//EquipWeapons[0] = DataAsset->Datas[0];

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	CheckNull(OwnerCharacter);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = OwnerCharacter;

	EquipWeapon[0] = OwnerCharacter->GetWorld()->SpawnActor<ACWeapon>(DataAsset->Datas[0].WeaponClass,SpawnParams);
	CheckNull(EquipWeapon[0]);

	EquipWeapon[0]->SetActorHiddenInGame(true);


}

void ACEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACEquipment::Equip(int32 slot)
{
	CheckNull(Montage);

	// ���� ��Ÿ�� ���
	OwnerCharacter->PlayAnimMontage(Montage);
	
	// ���� ��ȭ

	// ���� ���������� �ƴ���?
}

void ACEquipment::Begin_Equip()
{
	// ���� �� ���Ͽ� ���̱�
	EquipWeapon[0]->SetActorHiddenInGame(false);

	EquipWeapon[0]->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "hand_r");
}

void ACEquipment::End_Equip()
{
	// �ɷ� ����
}

