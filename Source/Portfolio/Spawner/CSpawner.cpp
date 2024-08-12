#include "Spawner/CSpawner.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "Enemy/CMonster.h"
#include "Enemy/CBoss.h"

ACSpawner::ACSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::GetClass(&MonsterClass, "/Game/Enemy/Monster/BP_CMonster");
	CheckNull(MonsterClass);

	CHelpers::GetClass(&BossClass, "/Game/Enemy/Boss/BP_CBoss");
	CheckNull(BossClass);

	Number = 5;
}

void ACSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	// GetWorld()->SpawnActorDeferred() <- �̰� ������� �� �����غ���
	// FinishSpawning()
}

void ACSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACSpawner::Spawn(FVector PlayerLocation, FName PlayerArea)
{
	
	// ������ ����,
	bool bSpawnBoss = false;

	for (int32 i = 0; i < Number; i++) // ��ȯ�� ������ ��ŭ �ݺ�
	{
		FVector SpawnLocation = SetSpawnRange(PlayerLocation);
		FTransform SpawnTM = FTransform(FRotator(), SpawnLocation, FVector(1));

		if (!bSpawnBoss)
		{
			if (FMath::FRand() < 0.8f)
			{
				// 80% Ȯ���� ������ �ڵ�� �̸� ��ȯ
				ACMonster* Monster = GetWorld()->SpawnActorDeferred<ACMonster>(MonsterClass, SpawnTM);
				CheckNull(Monster);

				Monster->SetMesh(PlayerArea);
				Monster->FinishSpawning(SpawnTM);

				Monster->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
			}
			else
			{
				// 20% Ȯ���� ������ �ڵ� ���� ��ȯ
				bSpawnBoss = true;
				ACBoss* Boss = GetWorld()->SpawnActor<ACBoss>(BossClass, SpawnTM);
				CheckNull(Boss);

				CLog::Print(Boss->GetActorRotation()); // �̰� �� �Ѱ��� -179�� ����?????????
				Boss->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
				
			}
		}
		else // ������ �̹� ���������̸� �������� ������ �̸� ��ȯ
		{
			ACMonster* Monster = GetWorld()->SpawnActorDeferred<ACMonster>(MonsterClass, SpawnTM);
			CheckNull(Monster);

			Monster->SetMesh(PlayerArea);
			Monster->FinishSpawning(SpawnTM);

			Monster->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}


}

FVector ACSpawner::SetSpawnRange(FVector PlayerLocation)
{
	float Radius = 500.0f; // ��: ������ 500 ���� ////////// ���߿� ���������� �� �͵�
	float ZRange = 200.0f; // Z �� ����: -200���� +200 ����

	// ���� ���� ��� (0���� 360�� ����)
	float Angle = FMath::RandRange(0.0f, 2 * PI);

	// ���� ������ �ȿ��� ������ ��ġ�� ��� (2D ��鿡��)
	float XOffset = Radius * FMath::Cos(Angle);
	float YOffset = Radius * FMath::Sin(Angle);

	// Z ���� �������� ��� (-ZRange ~ +ZRange)
	float ZOffset = FMath::RandRange(-ZRange, ZRange);

	// 3D �������� ���� ��ġ
	FVector RandomLocation = PlayerLocation + FVector(XOffset, YOffset, ZOffset);

	return RandomLocation;
}

