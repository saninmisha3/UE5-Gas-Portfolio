#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPlayerWidget.generated.h"

class UProgressBar;

UCLASS()
class PORTFOLIO_API UCPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	// AbilitySystemComponent�� AttributeSet�� ���ε��ϱ� ���� �Լ�
	void UpdateHealthBar(float Health);
	void UpdateStaminaBar(float Stamina);

	// ���׹̳��� ü�� �� ���� �� ȣ��� �Լ�
	void OnHealthChanged(float NewHealth);
	void OnStaminaChanged(float NewStamina);
public:
	UPROPERTY(meta = (BindWidget))
		UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* StaminaBar;

};
