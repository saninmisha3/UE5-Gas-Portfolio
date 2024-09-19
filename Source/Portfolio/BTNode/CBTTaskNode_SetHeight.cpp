#include "CBTTaskNode_SetHeight.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Enemy/CEnemyController.h"
#include "Enemy/CBoss.h"
#include "DataAsset/CBossDataAsset.h"
#include "CAnimInstance.h"

UCBTTaskNode_SetHeight::UCBTTaskNode_SetHeight()
{
	NodeName = "SetHeight";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_SetHeight::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
	CheckNullResult(AIC, EBTNodeResult::Failed);

	ACBoss* Boss = Cast<ACBoss>(AIC->GetPawn());
	CheckNullResult(Boss, EBTNodeResult::Failed);

	Boss->GetCharacterMovement()->Deactivate(); // ĳ���� �����Ʈ�� ��Ȱ���� �÷����� �����Ʈ�� ���.

	if (IsFly)
	{
		Boss->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag(FName("AI.State.Flying")));
		Boss->PlayAnimMontage(Boss->GetBossDataAsset()->MontageDatas.TakeOffMontage);
	}
	else
	{
		Boss->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.State.Flying")));
		Boss->PlayAnimMontage(Boss->GetBossDataAsset()->MontageDatas.LandMontage);
	}

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_SetHeight::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
	CheckNull(AIC);

	ACBoss* Boss = Cast<ACBoss>(AIC->GetPawn());
	CheckNull(Boss);

	if (IsFly)
		Boss->GetFloatingComp()->AddInputVector(FVector(0, 0, 1)); // ���� �ö󰡱� ��.
	else
		Boss->GetFloatingComp()->AddInputVector(FVector(0, 0, -1));

	if (!Boss->GetCurrentMontage()) 
	{
		UCAnimInstance* Anim = Cast<UCAnimInstance>(Boss->GetMesh()->GetAnimInstance());
		if (Anim)
		{
			if (IsFly)
			{
				Anim->IsFly = true;
			}
			else
			{
				Anim->IsFly = false;
			}
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
	
}
