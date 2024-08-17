#include "CPlayerWidget.h"
#include "Global.h"
#include "Components/ProgressBar.h"
#include "Player/CPlayer.h"

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
