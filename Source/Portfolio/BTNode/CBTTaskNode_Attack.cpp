#include "CBTTaskNode_Attack.h"
#include "Global.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Pet/CPetController.h"
#include "Pet/CPet.h"
#include "AbilitySystemComponent.h"
#include "GAS/GA/AI_Attack.h"

UCBTTaskNode_Attack::UCBTTaskNode_Attack()
{
	NodeName = "Attack";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// �ϴ� ���⼭ GA�� �ߵ���Ű�°� �켱������.
	if (OwnerComp.GetRootTree()->GetName() == FName("BT_Pet").ToString())
	{
		ACPetController* AIC = Cast<ACPetController>(OwnerComp.GetAIOwner());
		if (AIC)
		{
			ACPet* Pet = Cast<ACPet>(AIC->GetPawn());
			if (Pet)
			{
				if (Pet->GetAbilitySystemComponent())
				{
					
					Pet->GetAbilitySystemComponent()->TryActivateAbility(Pet->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_Attack::StaticClass())->Handle);
					return EBTNodeResult::InProgress;
				}
			}
		}
	}

	return EBTNodeResult::Failed;
}

void UCBTTaskNode_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (OwnerComp.GetRootTree()->GetName() == FName("BT_Pet").ToString())
	{
		ACPetController* AIC = Cast<ACPetController>(OwnerComp.GetAIOwner());
		if (AIC)
		{
			ACPet* Pet = Cast<ACPet>(AIC->GetPawn());
			if (Pet)
			{
				if (Pet->GetAbilitySystemComponent())
				{
					
					if (!Pet->GetAbilitySystemComponent()->GetCurrentMontage())
					{
						Pet->GetAbilitySystemComponent()->CancelAbilityHandle(Pet->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_Attack::StaticClass())->Handle);
						FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
					}
				}
			}
		}
	}
	
}
