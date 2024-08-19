#include "GAS/Attribute/CCharacterAttributeSet.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Widget/CPlayerWidget.h"

UCCharacterAttributeSet::UCCharacterAttributeSet()
{
	BaseHealth = 100.f;
	BaseStamina = 100.f;

	InitCurrentHealth(GetBaseHealth()); // current�� base���� ������
	InitCurrentStamina(GetBaseStamina());

}

void UCCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    // PreAttributeChange�� �Ӽ� ������ ������ �߻��ϱ� ���� �ڵ����� ȣ��˴ϴ�. ���� �Ӽ� ���� �����ϰų� �����ϱ⿡ ������ �����Դϴ�.
    if (Attribute == GetCurrentStaminaAttribute())  
    {
        NewValue = FMath::Clamp(NewValue, 0.0f, GetBaseStamina()+0.1f); // Todo.. �̻��� Ŭ������ �ɸ��°Ű����ѵ�..
    }
}

void UCCharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    // **PostAttributeChange**�� �Ӽ� ���� ����� �� ȣ��Ǵ� �Լ���, �� ���濡 ���� �ļ� �۾��̳� ���� ó���� �� �� �ִ� �߿��� ��ġ�Դϴ�.
    // �ַ� UI ������Ʈ, ���� ���� ó��, �����÷��� �̺�Ʈ�� ���õ� �ļ� �۾��� ó���� �� ���˴ϴ�.

    Super::PostAttributeChange(Attribute, OldValue, NewValue);

    if (Attribute == GetCurrentStaminaAttribute()) // ���׹̳��� ����ȰŸ�
    {
        OnStaminaChanged.Broadcast(NewValue); // UI����
    }
}

void UCCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    //PostGameplayEffectExecute�� Gameplay Effect�� ����� �Ŀ� ȣ��Ǵ� �Լ���, �� ����� ���� �ļ� �۾��� ó���ϴ� �� ���˴ϴ�. ���� ���, �Ӽ� ���� ����� �� UI�� �����ϰų�, Ư�� ������ ������ ��� �̺�Ʈ�� Ʈ�����ϴ� ���� �۾��� ó���� �� �ֽ��ϴ�.
}
