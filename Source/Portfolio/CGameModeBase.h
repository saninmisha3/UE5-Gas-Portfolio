#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CGameModeBase.generated.h"

class ACSpawner;
class ACBGMManager;

UCLASS()
class PORTFOLIO_API ACGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ACGameModeBase();

private:
	virtual void BeginPlay() override;

public:
	void Spawn();
	void Teleport(FName Area);
	void SetPlayerArea(AActor* OtherActor);

private:
	TSubclassOf<ACSpawner> SpawnerClass;
	ACSpawner* Spawner;

	FTimerHandle SpawnTimer;
	FName PlayerArea;
	
	TArray<AActor*> TargetPointActors;

	FString TargetPointName[5];

	ACBGMManager* BGMManager;
};
