#include "GAS/Attribute/CCharacterAttributeSet.h"

UCCharacterAttributeSet::UCCharacterAttributeSet()
{
	BaseHealth = 100.f;
	BaseStamina = 100.f;

	InitCurrentHealth(GetBaseHealth()); // current�� base���� ������
	InitCurrentStamina(GetBaseStamina());

}

void UCCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{

}

void UCCharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{

}

void UCCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    //Super::PostGameplayEffectExecute(Data);

    //// ���׹̳��� ü�� ���� ����Ǿ��� �� UI�� ������Ʈ�� �� �ֵ��� �˸�
    //if (Data.EvaluatedData.Attribute == GetBaseHealth())
    //{
    //    // Health ���� ����Ǿ��� �� ȣ��
    //    // ��: UI ������Ʈ
    //}
    //else if (Data.EvaluatedData.Attribute == GetBaseStamina())
    //{
    //    // Stamina ���� ����Ǿ��� �� ȣ��
    //    // ��: UI ������Ʈ
    //}
}
