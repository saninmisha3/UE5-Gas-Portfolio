#include "CWeaponAttributeSet.h"
#include "Global.h"

UCWeaponAttributeSet::UCWeaponAttributeSet()
{
	//if (IsBaseDamageSet && IsBaseProficiencySet)
	//{
	//	InitCurrentDamage(GetBaseDamage()); // current�� base���� ������
	//	InitCurrentProficiency(GetBaseProficiency());
	//}
	
}

void UCWeaponAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{

}

void UCWeaponAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{

}

void UCWeaponAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{

}
