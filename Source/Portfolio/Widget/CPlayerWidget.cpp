#include "CPlayerWidget.h"
#include "Global.h"
#include "Components/ProgressBar.h"
#include "Player/CPlayer.h"
#include "GAS/Attribute/CCharacterAttributeSet.h"

void UCPlayerWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // �������� ĳ������ AbilitySystemComponent�� ����
    ACPlayer* Player = Cast<ACPlayer>(GetOwningPlayerPawn());
    if(Player)
    {
        if (Player && Player->GetAbilitySystemComponent())
        {
            // ü�°� ���׹̳� ���� ����� ������ ȣ��Ǵ� �ݹ��� ����
            UpdateHealthBar(Player->GetAttributeSet()->GetCurrentHealth());
            UpdateStaminaBar(Player->GetAttributeSet()->GetCurrentStamina());
        }
    }

    if (Player->GetAttributeSet())
    {
        Player->GetAttributeSet()->OnHealthChanged.AddDynamic(this, &UCPlayerWidget::OnHealthChange);
        Player->GetAttributeSet()->OnStaminaChanged.AddDynamic(this, &UCPlayerWidget::OnStaminaChange);
    }
}

void UCPlayerWidget::UpdateHealthBar(float Health)
{
    if (HealthBar)
    {
        HealthBar->SetPercent(Health / 100.f);  // 0 ~ 100 ���̷� ���� ���
    }
}

void UCPlayerWidget::UpdateStaminaBar(float Stamina)
{
    if (StaminaBar)
    {
        StaminaBar->SetPercent(Stamina / 100.f);  // 0 ~ 100 ���̷� ���� ���
    }
}

void UCPlayerWidget::OnHealthChange(float NewHealth)
{
    UpdateHealthBar(NewHealth);
}

void UCPlayerWidget::OnStaminaChange(float NewStamina)
{
    UpdateStaminaBar(NewStamina);
}
