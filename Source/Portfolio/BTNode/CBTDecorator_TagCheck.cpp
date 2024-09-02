#include "BTNode/CBTDecorator_TagCheck.h"
#include "Global.h"
#include "Enemy/CEnemyController.h"
#include "Enemy/CEnemy.h"

UCBTDecorator_TagCheck::UCBTDecorator_TagCheck()
{
	NodeName = "CheckTags";
}

bool UCBTDecorator_TagCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
	CheckNullResult(AIC, false);

	ACEnemy* Enemy = Cast<ACEnemy>(AIC->GetPawn());
	CheckNullResult(Enemy, false);

	if (Enemy->GetTagContainer().HasTag(GameplayTag))
	{
		CLog::Print(GameplayTag.ToString()); // todo.. ���ڷ����͹����ΰŰ��� ���⼭ �� ������غ���
		return true;
	}
	PrintLine();
	return false;
}
