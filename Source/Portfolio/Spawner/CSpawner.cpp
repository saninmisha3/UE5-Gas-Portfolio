#include "Spawner/CSpawner.h"
#include "Global.h"
#include "Enemy/CEnemy.h"

ACSpawner::ACSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

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
	// ���⼭ �������� ������ �ؾ�����������?
	// ������ ���� /  �÷��̾� �ֺ� ����(�÷��̾� ��ġ�� ���� �ٸ�) / ���� ����.
	// ���Ǿ� Ʈ���̽�(�÷��̾���ġ�� ��Ʈ) ���� ����
	// ���� ���� Ȯ�� �ʿ�, ���� ���Ⱑ �縷���� �ʿ�����?
	// ���� ���͸� ��ȯ����.

	void SetSpawnRange(); // �÷��̾� ��ġ �˾ƾ���, �̰� ���Ӹ�尡 �˷�����
	void SelectEnemy(); // �̰� 
}

