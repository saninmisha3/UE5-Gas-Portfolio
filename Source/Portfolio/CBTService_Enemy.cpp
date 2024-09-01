#include "CBTService_Enemy.h"
#include "Global.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/CEnemyController.h"
#include "Enemy/CEnemy.h"

UCBTService_Enemy::UCBTService_Enemy()
{
	NodeName = "RootService";

	bTickIntervals = true;
}

void UCBTService_Enemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
	CheckNull(AIC);

	ACEnemy* Enemy = Cast<ACEnemy>(AIC->GetPawn());
	CheckNull(Enemy);

	//if (AIC->GetBlackboardComponent()->GetValueAsObject("PlayerKey")) // �÷��̾ �����ϸ� �Ѵ� ���·�,
	//{
	//	if (Enemy->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag("AI.State.Idle")))
	//	{
	//		Enemy->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag("AI.State.Idle"));
	//	}
	//	
	//	if (!Enemy->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag("AI.State.Approach")))
	//	{
	//		Enemy->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag("AI.State.Approach"));
	//	}
	//}
	//else
	//{
	//	if (Enemy->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag("AI.State.Approach")))
	//	{
	//		Enemy->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag("AI.State.Approach"));
	//	}

	//	if (!Enemy->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag("AI.State.Idle")))
	//	{
	//		Enemy->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag("AI.State.Idle"));
	//	}
	//}
	if(Enemy->GetTagContainer())
		CLog::Print(Enemy->GetTagContainer().Num()); // �����µ� ��� 0�̶�, �±װ� �ȵ������ִ�.

}
