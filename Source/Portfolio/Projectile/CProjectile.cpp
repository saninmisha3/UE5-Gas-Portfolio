#include "CProjectile.h"
#include "Global.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "Player/CPlayer.h"
#include "Enemy/CEnemy.h"
#include "GAS/GE/Damage.h"
#include "GAS/Attribute/CMonsterAttributeSet.h"
#include "Pet/CPet.h"
#include "GAS/Attribute/CPetAttributeSet.h"

ACProjectile::ACProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &RootComp, "RootComp");
	CheckNull(RootComp);

	CHelpers::CreateSceneComponent(this, &ParticleComp, "ParticleComp", RootComp);
	CheckNull(ParticleComp);

	CHelpers::CreateSceneComponent(this, &BoxComp, "BoxComp", RootComp);
	CheckNull(BoxComp);

	CHelpers::CreateActorComponent(this, &ProjectileComp, "ProjectileComp");
	CheckNull(ProjectileComp);
}

void ACProjectile::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACProjectile::OnBoxBeginOverlap);
}

void ACProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACProjectile::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ���⼭ �ε��� ���� �ǰ� ��ƼŬ �߰� + ���� ���� + (���� �߰�)
	// �� �۾��ϱ����� GE�� ���� �� �� �˾ƺ��� �� ��, ������ �ȵ�

	if (OtherActor->IsA<ACPlayer>())
		return;

	if (OtherActor->IsA<ACEnemy>())
	{
		ACEnemy* Enemy = Cast<ACEnemy>(OtherActor);
		if (Enemy && Enemy->GetAbilitySystemComponent())
		{
			UDamage* GE = NewObject<UDamage>(this, UDamage::StaticClass());
			GE->SetModify(GetOwner(),OtherActor);

			FGameplayEffectContextHandle EffectContext = Enemy->GetAbilitySystemComponent()->MakeEffectContext();
			FGameplayEffectSpecHandle EffectSpecHandle = Enemy->GetAbilitySystemComponent()->MakeOutgoingSpec(GE->GetClass(), 1.0f, EffectContext);

			FGameplayEffectSpec* EffectSpec = EffectSpecHandle.Data.Get();

			Enemy->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpec, Enemy->GetAbilitySystemComponent());
		}
	}
}

