#include "CMonsterAttributeSet.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "Widget/CEnemyHealthWidget.h"

UCMonsterAttributeSet::UCMonsterAttributeSet()
{

}

void UCMonsterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
}

void UCMonsterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	// ������Ÿ�ϰ� �ε����� ������� �� ����

	CLog::Print(OldValue);
	CLog::Print(NewValue);

	if (OldValue > NewValue) // ü���� ����������
	{
		ACEnemy* Enemy = Cast<ACEnemy>(GetOwningActor());
		if (Enemy)
		{
			PrintLine();
			Enemy->GetHealthWidget()->Update(NewValue, GetBaseHealth()); // ��������Ʈ�� �غ���.

			Enemy->GetTagContainer().Reset();
			Enemy->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag(FName("AI.State.GetHit")));
		}
		// �´� ��Ÿ�� <- �̰� �����Ϳ��� �ȿ� ��Ÿ�ָ� ����Ѵٴ� ���ε� ��ƹ��Ʈ���� �ϴ°� �³�?
		// �Ӹ����� ����ǥ
	}
}

void UCMonsterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
}
