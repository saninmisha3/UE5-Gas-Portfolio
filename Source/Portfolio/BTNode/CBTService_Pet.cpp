#include "CBTService_Pet.h"
#include "Global.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Pet/CPetController.h"
#include "Pet/CPet.h"
#include "Enemy/CEnemy.h"
#include "Player/CPlayer.h"

UCBTService_Pet::UCBTService_Pet()
{
	NodeName = "RootService";

	bTickIntervals = true;
}

void UCBTService_Pet::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACPetController* AIC = Cast<ACPetController>(OwnerComp.GetAIOwner());
	CheckNull(AIC);

	ACPet* Pet = Cast<ACPet>(AIC->GetPawn());
	CheckNull(Pet);

	ACPlayer* Player = Cast<ACPlayer>(AIC->GetBlackboardComponent()->GetValueAsObject("PlayerKey"));
	ACEnemy* Enemy = Cast<ACEnemy>(AIC->GetBlackboardComponent()->GetValueAsObject("EnemyKey"));

	AIC->GetBlackboardComponent()->SetValueAsVector("PlayerLocation", Pet->GetOwner()->GetActorLocation()); // �̰� �ȵǰ����� �����νľȵǴµ�

	CLog::Print(Pet->GetOwner()->GetName()); // �� ��Ʈ�ѷ�������?

	/*
	1. �÷��̾�� �־����� = �÷��̾� ��ó�� �ٰ����� ( ��ũ���ǵ� ������ )
	2. �÷��̾� ��ó�̰� + �ֺ��� ���Ͱ� ������ = ���� (EQS)
	3. �÷��̾� ��ó�̰� + �ֺ��� ���Ͱ� �ְ� + ���ݹ��� ���̸� = ����
	4. �÷��̾� ��ó�̰� + �ֺ��� ���Ͱ� �ְ� + ���ݹ��� ���̸� = ����
	*/


	if (Player)
	{
		if (Enemy)
		{
			float DistanceToEnemy = Pet->GetDistanceTo(Enemy);

			if (DistanceToEnemy < 150.f)
			{
				Pet->GetTagContainer().Reset();
				Pet->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag(FName("Pet.State.Attack")));
			}
			Pet->GetTagContainer().Reset();
			Pet->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag(FName("Pet.State.Approach")));
		}
		Pet->GetTagContainer().Reset();
		Pet->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag("Pet.State.Patrol"));
	}

	Pet->GetTagContainer().Reset();
	Pet->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag("Pet.State.ChasingPlayer"));

}
