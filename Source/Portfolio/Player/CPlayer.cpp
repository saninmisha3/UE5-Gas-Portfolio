#include "CPlayer.h"
#include "Global.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Portal/CPortal.h"
#include "Engine/TriggerVolume.h"
#include "CGameModeBase.h"
#include "AbilitySystemComponent.h"
#include "GAS/Attribute/CCharacterAttributeSet.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set SkeletalMesh
	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Assets/CR/LQ/Modular_001_Bergs10/Mesh/SKM_Bergs10_1");
	CheckNull(MeshAsset);
	
	GetMesh()->SetSkeletalMesh(MeshAsset);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	// Set Components
	CHelpers::CreateSceneComponent(this, &SpringArmComp, "SpringArmComp",GetMesh());
	CheckNull(SpringArmComp);

	SpringArmComp->TargetArmLength = 200.f;
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 150));
	SpringArmComp->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;

	CHelpers::CreateSceneComponent(this, &CameraComp, "CameraComp",SpringArmComp);
	CameraComp->SetRelativeLocation(FVector(0, 70, 0));

	GetCharacterMovement()->MaxWalkSpeed = 400.f; // ���߿� �����ؾ� �� �̷��� �������Ҳ���
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->bOrientRotationToMovement = true; 

	// Set AnimClass;
	CHelpers::GetClass(&AnimClass,"/Game/Player/ABP_CPlayer");
	CheckNull(AnimClass);

	// Set GAS
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>("ASC");
	CheckNull(ASC);

	AttributeSet = CreateDefaultSubobject<UCCharacterAttributeSet>("AttributeSet");
	CheckNull(AttributeSet);

		
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->SetAnimClass(AnimClass);

	OnActorBeginOverlap.AddDynamic(this, &ACPlayer::BeginOverlap);

	ASC->InitAbilityActorInfo(this, this);
	
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput); // ������ ����, �ɼǿ��� ���������ϰ�
	PlayerInputComponent->BindAxis("Lookup", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ACPlayer::OnSprint); // �̰͵� ���߿� GAS�� ������ ���� ����
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ACPlayer::OffSprint);

	PlayerInputComponent->BindAction("Summon", IE_Pressed, this, &ACPlayer::OnSummon);
}

UAbilitySystemComponent* ACPlayer::GetAbilitySystemComponent() const
{
	return ASC;
}

void ACPlayer::OnMoveForward(float Axis)
{
	FRotator ControlRot = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Direction = FQuat(ControlRot).GetForwardVector();

	AddMovementInput(Direction, Axis);
}

void ACPlayer::OnMoveRight(float Axis)
{
	FRotator ControlRot = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Direction = FQuat(ControlRot).GetRightVector();

	AddMovementInput(Direction, Axis);
}

void ACPlayer::OnSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void ACPlayer::OffSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
}

void ACPlayer::OnSummon()
{
	//Todo.. �� �����ؾ���
}

void ACPlayer::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor == Cast<ACPortal>(OtherActor)) // ��Ż�� �ε�����
		GetCharacterMovement()->StopMovementImmediately(); // �̰� bCanMove ���� ��������.

	if (OtherActor->IsA(ATriggerVolume::StaticClass())) // Ʈ���� ������ �ε����� !���࿡ �����±� �����ؾ� �ϸ� ���⼭ for���ɱ�
	{
		ACGameModeBase* MyGameMode = Cast<ACGameModeBase>(GetWorld()->GetAuthGameMode());
		CheckNull(MyGameMode);
		
		MyGameMode->SetPlayerArea(OtherActor);
	}
}

