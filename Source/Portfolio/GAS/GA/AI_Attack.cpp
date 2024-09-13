#include "AI_Attack.h"
#include "Global.h"
#include "GAS/GE/Damage.h"
#include "Pet/CPet.h"
#include "DataAsset/CPetDataAsset.h"

void UAI_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	// MontageToPlay�� ���ϴ°� �ֱ�
	// �� �Լ��� ĵ�� �����Ƽ�� ȣ��Ǳ���� ��� �ߵ���
	ACPet* Pet = Cast<ACPet>(OwnerInfo->AvatarActor);
	if (Pet)
	{
		if (Pet->GetDataAsset())
		{
			MontageToPlay = Pet->GetDataAsset()->MontageDatas.AttackMontage[0];
		}
	}

	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData); 

}
