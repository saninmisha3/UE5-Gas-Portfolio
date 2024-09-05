#include "Summon.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Pet/CPetController.h"
#include "Pet/CPet.h"

USummon::USummon()
{
	CHelpers::GetClass(&PetClass, "/Game/Pet/BP_CPet");
	CheckNull(PetClass);
}

void USummon::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	PetController = ActorInfo->OwnerActor->GetWorld()->SpawnActor<ACPetController>(ACPetController::StaticClass());
	CheckNull(PetController);

	FTransform SpawnTM; // Todo.. ���߿� ��ġ�� ȸ�� ����غ���
	SpawnTM.SetLocation(ActorInfo->AvatarActor->GetActorLocation() + FVector(0, 100, 0));

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Cast<AActor>(ActorInfo->AvatarActor);

	CLog::Print(SpawnParams.Owner->GetName()); // ����� ���ʰ� �÷��̾��� �߳����µ�?

	Pet = ActorInfo->OwnerActor->GetWorld()->SpawnActor<ACPet>(PetClass, SpawnTM, SpawnParams);
	CheckNull(Pet);

	CLog::Print(Pet->GetName()); // ���񽺿��� ��Ÿ���� ���� ����

	PetController->Possess(Pet);
}

void USummon::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	if (PetController)
	{
		PetController->UnPossess();
		PetController->Destroy();
	}
		
	if(Pet)
		Pet->Destroy();
}
