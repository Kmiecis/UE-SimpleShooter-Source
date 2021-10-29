#include "ShooterCharacter.h"

#include "Gun.h"

AShooterCharacter::AShooterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	auto* ActorMesh = GetMesh();
	FName WeaponBoneName = TEXT("weapon_r");
	int32 BoneIndex = ActorMesh->GetBoneIndex(WeaponBoneName);
	if (BoneIndex != INDEX_NONE)
	{
		ActorMesh->HideBone(BoneIndex, EPhysBodyOp::PBO_None);
	}

	FName WeaponSocket = TEXT("WeaponSocket");
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	Gun->AttachToComponent(ActorMesh, FAttachmentTransformRules::KeepRelativeTransform, WeaponSocket);
	Gun->SetOwner(this);
}

void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	FVector Forward = GetActorForwardVector();
	AddMovementInput(Forward * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	FVector Right = GetActorRightVector();
	AddMovementInput(Right * AxisValue);
}
