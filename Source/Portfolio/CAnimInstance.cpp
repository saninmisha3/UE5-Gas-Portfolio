#include "CAnimInstance.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Enemy/CEnemy.h"

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner()); // �÷��̾�Ӹ� �ƴ϶� �����̴� ĳ���� ��� ����ؼ� ACPlayer�� ĳ����x
	CheckNull(OwnerCharacter);

	Speed = OwnerCharacter->GetVelocity().Size2D();
	Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation());

	if (Cast<ACPlayer>(OwnerCharacter))
	{
		ACPlayer* Player = Cast<ACPlayer>(OwnerCharacter);

		TagContainer = Player->GetTagContainer();
	}
	else if (Cast<ACEnemy>(OwnerCharacter))
	{
		ACEnemy* Enemy = Cast<ACEnemy>(OwnerCharacter);

		TagContainer = Enemy->GetTagContainer();
	}
}

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}