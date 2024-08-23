#pragma once

#include "CoreMinimal.h"
#include "CWeapon.h"
#include "CRifle.generated.h"

UCLASS()
class PORTFOLIO_API ACRifle : public ACWeapon
{
	GENERATED_BODY()
	
public:	
	ACRifle();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};
