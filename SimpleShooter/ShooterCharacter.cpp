#include "ShooterCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Gun.h"
#include "SimpleShooterGameModeBase.h"

AShooterCharacter::AShooterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
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
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	auto* ActorMesh = GetMesh();
	auto BoneIndex = ActorMesh->GetBoneIndex(TEXT("weapon_r"));
	if (BoneIndex != INDEX_NONE)
	{
		ActorMesh->HideBone(BoneIndex, EPhysBodyOp::PBO_None);
	}

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	Gun->AttachToComponent(ActorMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	DamageApplied = FMath::Min(DamageApplied, Health);
	Health -= DamageApplied;

	if (IsDead())
	{
		if (auto* ActorCapsule = GetCapsuleComponent())
		{
			ActorCapsule->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
		}

		if (auto* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>())
		{
			GameMode->PawnKilled(this);
		};

		DetachFromControllerPendingDestroy();
	}

	return DamageApplied;
}

void AShooterCharacter::Shoot()
{
	Gun->PullTrigger();
}

bool AShooterCharacter::IsDead() const
{
	return Health <= 0.0f;
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	auto ForwardVector = GetActorForwardVector();
	AddMovementInput(ForwardVector * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	auto RightVector = GetActorRightVector();
	AddMovementInput(RightVector * AxisValue);
}
