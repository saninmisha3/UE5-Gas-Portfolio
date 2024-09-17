#include "AI_Attack.h"
#include "Global.h"
#include "GAS/GE/Damage.h"
#include "Pet/CPet.h"
#include "DataAsset/CPetDataAsset.h"
#include "Enemy/CEnemy.h"
#include "DataAsset/CMonsterMeshDataAsset.h"

void UAI_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	// �� �Լ��� ĵ�� �����Ƽ�� ȣ��Ǳ���� ��� �ߵ���
	if (OwnerInfo->AvatarActor->IsA<ACPet>())
	{
		ACPet* Pet = Cast<ACPet>(OwnerInfo->AvatarActor);
		if (Pet)
		{
			if (Pet->GetDataAsset())
			{
				MontageToPlay = Pet->GetDataAsset()->MontageDatas.AttackMontage[0];
			}
		}
	}
	else if (OwnerInfo->AvatarActor->IsA<ACEnemy>())
	{
		ACEnemy* Enemy = Cast<ACEnemy>(OwnerInfo->AvatarActor);
		if (Enemy)
		{
			if (Enemy->GetDataAsset())
			{	
				MontageToPlay = Enemy->GetDataAsset()->Datas[Enemy->GetIndex()].MontageDatas.AttackMontage[0]; // �̰� �����߰��Ǹ� �װ� �ǰ� �ؾ�������?
			}
		}
	}

	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData); 
}
