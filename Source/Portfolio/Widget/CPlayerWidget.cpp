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

void UCPlayerWidget::OnHealthChanged(float NewHealth)
{
    UpdateHealthBar(NewHealth);
}

void UCPlayerWidget::OnStaminaChanged(float NewStamina)
{
    UpdateStaminaBar(NewStamina);
}
