#include "BTNode/CBTService_Boss.h"
#include "Global.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/CEnemyController.h"
#include "Enemy/CBoss.h"
#include "Player/CPlayer.h"
#include "Pet/CPet.h"
#include "CAnimInstance.h"

UCBTService_Boss::UCBTService_Boss()
{
	NodeName = "BoosService";

	bTickIntervals = true;
}

void UCBTService_Boss::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACEnemyController* AIC = Cast<ACEnemyController>(OwnerComp.GetAIOwner());
	CheckNull(AIC);

	ACBoss* Boss = Cast<ACBoss>(AIC->GetPawn());
	CheckNull(Boss);

	ACPlayer* Player = Cast<ACPlayer>(AIC->GetBlackboardComponent()->GetValueAsObject("PlayerKey"));
	ACPet* Pet = Cast<ACPet>(AIC->GetBlackboardComponent()->GetValueAsObject("PetKey"));

	SetTarget(AIC, Boss, Player, Pet);

	if (AIC->GetBlackboardComponent()->GetValueAsObject("AttackTargetKey")) // Ÿ���� �����Ǹ�
	{
		Boss->SetWidget(true);

		UCAnimInstance* Anim = Cast<UCAnimInstance>(Boss->GetMesh()->GetAnimInstance());
		CheckNull(Anim);

		AActor* Target = Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject("AttackTargetKey"));
		CheckNull(Target);

		float DistanceToTarget = Boss->GetDistanceTo(Target);
		float AttackRange = Anim->IsFly ? 3500.f : 1500.f;

		if(DistanceToTarget < AttackRange)
		{
			if (Boss->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Patrol"))))
				Boss->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Patrol")));
			if (Boss->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Approach"))))
				Boss->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Approach")));
			if (!Boss->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Attack"))))
				Boss->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Attack")));
		}
		else
		{
			if (Boss->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Patrol"))))
				Boss->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Patrol")));
			if (Boss->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Attack"))))
				Boss->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Attack")));
			if (!Boss->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Approach"))))
				Boss->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Approach")));
		}
	}
	else
	{
		Boss->SetWidget(false); // ���� �ڲ� �� �̷���

		if(Boss->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Approach"))))
			Boss->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Approach")));
		if (Boss->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Attack"))))
			Boss->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Attack")));
		if (!Boss->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Patrol"))))
			Boss->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Patrol")));
	}
}

void UCBTService_Boss::SetTarget(ACEnemyController* AIC, ACBoss* Boss, ACPlayer* Player, ACPet* Pet)
{
	float DistanceToPlayer = 0.0f;
	float DistanceToPet = 0.0f;

	if (Player != nullptr && !(Player->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("Character.State.Dead")))))
	{
		DistanceToPlayer = Boss->GetDistanceTo(Player);
	}

	if (Pet != nullptr && !(Pet->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Dead")))))
	{
		DistanceToPet = Boss->GetDistanceTo(Pet);
	}

	if (DistanceToPlayer >= DistanceToPet)
	{
		AIC->GetBlackboardComponent()->SetValueAsObject("AttackTargetKey", Player);
	}
	else
	{
		AIC->GetBlackboardComponent()->SetValueAsObject("AttackTargetKey", Pet);
	}
}