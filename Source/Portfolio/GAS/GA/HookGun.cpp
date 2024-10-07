#include "HookGun.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Camera/CameraComponent.h"
#include "Engine/TimerHandle.h"
#include "Weapon/CHookGun.h"
#include "CableComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/Attribute/CCharacterAttributeSet.h"

UHookGun::UHookGun()
{
	CHelpers::GetAsset(&AttackMontage, "/Game/Assets/Montage/Fire_Rifle_Ironsights_Montage");
	CheckNull(AttackMontage);

	CHelpers::GetClass(&BPHookGunEffect, "/Game/GAS/BP_GE_HookGun");
	CheckNull(BPHookGunEffect);
}

void UHookGun::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	ACPlayer* Player = Cast<ACPlayer>(GetOwningActorFromActorInfo()->GetOwner());
	CheckNull(Player);

	if (Player->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("Character.State.StaminaEmpty"))) || Player->GetAttributeSet()->GetCurrentStamina() <= 50.f)
	{
		return;
	}

	Player->PlayAnimMontage(AttackMontage); 
	if (!GetWorld()->GetTimerManager().IsTimerActive(TraceTimerHandle)) 	{
		GetWorld()->GetTimerManager().SetTimer(TraceTimerHandle, this, &UHookGun::FireHook, 0.05f, true);
	}

	if (!GetWorld()->GetTimerManager().IsTimerActive(EndTimerHandle)) 	{
		GetWorld()->GetTimerManager().SetTimer(EndTimerHandle, this, &UHookGun::FireEnd, 1.f, false);
	}

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UHookGun::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	if (GetWorld()->GetTimerManager().IsTimerActive(TraceTimerHandle)) return; 	
	ACHookGun* HookGun = Cast<ACHookGun>(GetOwningActorFromActorInfo());
	CheckNull(HookGun);

	ACPlayer* Player = Cast<ACPlayer>(HookGun->GetOwner());
	CheckNull(Player);

	GetWorld()->GetTimerManager().ClearTimer(EndTimerHandle);

	HookGun->GetCableComp()->CableLength = 0.f; 
		HookGun->GetCableComp()->EndLocation = FVector(0);

	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UHookGun::FireHook()
{
	if (!this->IsActive()) return; 
	ACHookGun* HookGun = Cast<ACHookGun>(GetOwningActorFromActorInfo());
	CheckNull(HookGun);

    ACPlayer* Player = Cast<ACPlayer>(HookGun->GetOwner());
    CheckNull(Player);

    FVector Start = HookGun->GetActorLocation();
    FVector End = Start + Player->GetCameraComp()->GetForwardVector() * HookGun->GetCableComp()->CableLength;

    FHitResult HitResult;
    TArray<AActor*> IgnoreActors;

	FCollisionObjectQueryParams Parms;
	Parms.AddObjectTypesToQuery(ECC_WorldStatic);

	if (GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, Parms))
	{
		FGameplayEffectContextHandle EffectContext = Player->GetAbilitySystemComponent()->MakeEffectContext();
		FGameplayEffectSpecHandle EffectSpecHandle = Player->GetAbilitySystemComponent()->MakeOutgoingSpec(BPHookGunEffect, 1.0f, EffectContext);

		Player->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

		HookGun->GetCableComp()->EndLocation = HitResult.Location;

		SplineLaunch(HitResult.Location);

		GetWorld()->GetTimerManager().ClearTimer(TraceTimerHandle);

		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
	}
    else
	{
		HookGun->GetCableComp()->EndLocation = HookGun->GetTransform().InverseTransformPosition(End);         HookGun->GetCableComp()->CableLength += 200.f;
    }
}

void UHookGun::SplineLaunch(FVector HitLocation)
{
	ACHookGun* HookGun = Cast<ACHookGun>(GetOwningActorFromActorInfo());
	CheckNull(HookGun);

	ACPlayer* Player = Cast<ACPlayer>(HookGun->GetOwner());
	CheckNull(Player);

	HookGun->GetSplineComp()->AddSplinePoint(Player->GetActorLocation(), ESplineCoordinateSpace::World);
	HookGun->GetSplineComp()->AddSplinePoint(HitLocation, ESplineCoordinateSpace::World);
	HookGun->GetSplineComp()->UpdateSpline();

	FVector LaunchLocation = HookGun->GetSplineComp()->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
	FVector LaunchDirection = (LaunchLocation - Player->GetActorLocation()).GetSafeNormal();

	Player->LaunchCharacter(LaunchDirection * 3000.f, true, true);
}

void UHookGun::FireEnd()
{
	GetWorld()->GetTimerManager().ClearTimer(TraceTimerHandle);
	
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
}

