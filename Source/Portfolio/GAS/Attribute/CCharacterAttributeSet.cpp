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
    // PreAttributeChange�� �Ӽ� ������ ������ �߻��ϱ� ���� �ڵ����� ȣ��˴ϴ�. ���� �Ӽ� ���� �����ϰų� �����ϱ⿡ ������ �����Դϴ�. 
}

void UCCharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    // **PostAttributeChange**�� �Ӽ� ���� ����� �� ȣ��Ǵ� �Լ���, �� ���濡 ���� �ļ� �۾��̳� ���� ó���� �� �� �ִ� �߿��� ��ġ�Դϴ�.
    // �ַ� UI ������Ʈ, ���� ���� ó��, �����÷��� �̺�Ʈ�� ���õ� �ļ� �۾��� ó���� �� ���˴ϴ�.
}

void UCCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    // ���׹̳��� ü�� ���� ����Ǿ��� �� UI�� ������Ʈ�� �� �ֵ��� �˸�
    if (Data.EvaluatedData.Attribute == GetBaseHealth())
    {
        // Health ���� ����Ǿ��� �� ȣ��
        // ��: UI ������Ʈ
    }
    else if (Data.EvaluatedData.Attribute == GetBaseStamina())
    {
        // Stamina ���� ����Ǿ��� �� ȣ��
        // ��: UI ������Ʈ
    }


    //PostGameplayEffectExecute�� Gameplay Effect�� ����� �Ŀ� ȣ��Ǵ� �Լ���, �� ����� ���� �ļ� �۾��� ó���ϴ� �� ���˴ϴ�. ���� ���, �Ӽ� ���� ����� �� UI�� �����ϰų�, Ư�� ������ ������ ��� �̺�Ʈ�� Ʈ�����ϴ� ���� �۾��� ó���� �� �ֽ��ϴ�.
}
