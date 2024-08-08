#include "CGameModeBase.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "AbilitySystemGlobals.h"
#include "Spawner/CSpawner.h"
#include "Engine/TriggerVolume.h"

ACGameModeBase::ACGameModeBase()
{
	UAbilitySystemGlobals::Get().InitGlobalData();

	// Set DefaultPawnClass
	TSubclassOf<ACPlayer> PlayerClass;
	CHelpers::GetClass(&PlayerClass, "/Script/Engine.Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'");
	CheckNull(PlayerClass);

	DefaultPawnClass = PlayerClass;
	
}

void ACGameModeBase::BeginPlay()
{
	TArray<AActor*, FDefaultAllocator> Areas;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATriggerVolume::StaticClass(), Areas); // ���忡 ��ġ�� Ʈ���ŵ� ��������
	if (Areas.Num() < 0) return;

	for (const auto& Area : Areas)
	{
		AActor* PlayerStart = FindPlayerStart(GetWorld()->GetFirstPlayerController())z;
		CheckNull(PlayerStart);

		if (PlayerStart->IsOverlappingActor(Area)) // �÷��̾� ��ŸƮ�� �ִ� ���� �ʱ�ȭ
		{
			SetPlayerArea(Area);
			CLog::Print(Area->GetName());
			break;
		}
	}
	
	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &ACGameModeBase::Spawn, 5.f, true); // 5�ʸ��� �����Լ� ����
}

void ACGameModeBase::Spawn()
{
	ACPlayer* Player = Cast<ACPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	CheckNull(Player);

	Spawner->Spawn(Player->GetActorLocation(), PlayerArea);
}

void ACGameModeBase::Teleport()
{
	// ���߿� ����
}

void ACGameModeBase::SetPlayerArea(AActor* OtherActor) // �÷��̾� ���� �ٲٱ�
{
	for (const auto& MyTags : OtherActor->Tags)
		PlayerArea = MyTags;

	CLog::Print(PlayerArea.ToString());
}
