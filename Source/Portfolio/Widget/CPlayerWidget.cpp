#include "CPlayerWidget.h"
#include "Global.h"
#include "Components/ProgressBar.h"
#include "Player/CPlayer.h"
#include "GAS/Attribute/CCharacterAttributeSet.h"
#include "Pet/CPet.h"
#include "GAS/Attribute/CPetAttributeSet.h"

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

    ACPet* Pet = nullptr;

    TArray<AActor*> Actors;
    Player->GetAttachedActors(Actors);

    if (Actors.Num() > 0)
    {
        for (const auto& Actor : Actors)
        {
            if (Actor->IsA<ACPet>())
            {
                Pet = Cast<ACPet>(Actor);
                break;
            }
        }
    }

    if (Pet)
    {
        if (Pet && Pet->GetAbilitySystemComponent())
        {
            // ü�°� ���׹̳� ���� ����� ������ ȣ��Ǵ� �ݹ��� ����
            UpdateHealthBar(Pet->GetAttributeSet()->GetCurrentHealth());
        }
        if (Pet->GetAttributeSet())
        {
            Pet->GetAttributeSet()->OnHealthChanged.AddDynamic(this, &UCPlayerWidget::OnHealthChange);
        }
    }

}

void UCPlayerWidget::UpdateHealthBar(float Health)
{
    if (PlayerHealthBar)
    {
        PlayerHealthBar->SetPercent(Health / 100.f);  // 0 ~ 100 ���̷� ���� ���
    }
}

void UCPlayerWidget::UpdateStaminaBar(float Stamina)
{
    if (PlayerStaminaBar)
    {
        PlayerStaminaBar->SetPercent(Stamina / 100.f);  // 0 ~ 100 ���̷� ���� ���
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
