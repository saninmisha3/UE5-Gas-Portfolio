#include "Spawner/CSpawner.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "Enemy/CMonster.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enemy/CEnemyController.h"

ACSpawner::ACSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::GetClass(&MonsterClass, "/Game/Enemy/Monster/BP_CMonster");
	CheckNull(MonsterClass);

	Number = 5;
}

void ACSpawner::BeginPlay()
{
	Super::BeginPlay();

}

void ACSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACSpawner::Spawn(FVector PlayerLocation, FName PlayerArea)
{
	for (int32 i = 0; i < Number; i++) // ��ȯ�� ������ ��ŭ �ݺ�
	{
		ACEnemyController* EnemyController = GetWorld()->SpawnActor<ACEnemyController>();
		CheckNull(EnemyController);

		FVector SpawnLocation = SetSpawnRange(PlayerLocation);
		FTransform SpawnTM = FTransform(FRotator(), SpawnLocation, FVector(1));

		ACMonster* Monster = GetWorld()->SpawnActorDeferred<ACMonster>(MonsterClass, SpawnTM);
		CheckNull(Monster);

		Monster->SetMesh(PlayerArea);
		EnemyController->Possess(Monster);

		Monster->FinishSpawning(SpawnTM);

		Monster->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));

	}
}

FVector ACSpawner::SetSpawnRange(FVector PlayerLocation)
{
	float Radius = 500.0f; // ��: ������ 500 ���� ////////// todo.. ���߿� ���������� �� �͵�
	float ZRange = 200.0f; // Z �� ����: -200���� +200 ����

	// ���� ���� ��� (0���� 360�� ����)
	float Angle = FMath::RandRange(0.f, 2 * PI);

	// ���� ������ �ȿ��� ������ ��ġ�� ��� (2D ��鿡��)
	float XOffset = Radius * FMath::Cos(Angle);
	float YOffset = Radius * FMath::Sin(Angle);

	// Z ���� �������� ��� (-ZRange ~ +ZRange)
	float ZOffset = FMath::RandRange(-ZRange, ZRange);

	// 3D �������� ���� ��ġ
	FVector RandomLocation = PlayerLocation + FVector(XOffset, YOffset, ZOffset);

	return RandomLocation;
}

