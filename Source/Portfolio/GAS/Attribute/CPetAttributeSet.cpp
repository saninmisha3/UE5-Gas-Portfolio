#include "GAS/Attribute/CPetAttributeSet.h"

UCPetAttributeSet::UCPetAttributeSet()
{

}

void UCPetAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
}

void UCPetAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::PostAttributeChange(Attribute, OldValue, NewValue);

    if (Attribute == GetCurrentHealthAttribute()) // ���׹̳��� ����ȰŸ�
    {
        OnHealthChanged.Broadcast(NewValue); // UI����
    }
}

void UCPetAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
}
