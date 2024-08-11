#include "CAnimInstance.h"
#include "Global.h"
#include "Player/CPlayer.h"

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* OwnerPawn = TryGetPawnOwner(); // �÷��̾�Ӹ� �ƴ϶� �����̴� ĳ���� ��� ����ؼ� ACPlayer�� ĳ����x
	CheckNull(OwnerPawn);

	Speed = OwnerPawn->GetVelocity().Size2D();
	Direction = CalculateDirection(OwnerPawn->GetVelocity(), OwnerPawn->GetControlRotation()); 
}

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}