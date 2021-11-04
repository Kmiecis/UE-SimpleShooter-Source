#include "Gun.h"

#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	FHitResult HitResult;
	FVector ShotDirection;
	bool HitSuccess = GunTrace(HitResult, ShotDirection);
	if (HitSuccess)
	{
		auto HitPoint = HitResult.ImpactPoint;
		auto HitRotation = (-ShotDirection).Rotation();

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, HitPoint, HitRotation);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, HitPoint, HitRotation);

		if (auto* DamageActor = HitResult.GetActor())
		{
			auto DamageEvent = FPointDamageEvent(Damage, HitResult, ShotDirection, nullptr);
			auto* OwnerController = GetOwnerController();
			DamageActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}

AController* AGun::GetOwnerController() const
{
	if (auto* OwnerPawn = Cast<APawn>(GetOwner()))
	{
		return OwnerPawn->GetController();
	}
	return nullptr;
}

bool AGun::GunTrace(FHitResult& HitResult, FVector& ShotDirection)
{
	if (auto* OwnerController = GetOwnerController())
	{
		FVector ViewLocation;
		FRotator ViewRotation;
		OwnerController->GetPlayerViewPoint(ViewLocation, ViewRotation);

		ShotDirection = ViewRotation.Vector();
		auto EndLocation = ViewLocation + ShotDirection * MaxRange;

		FCollisionQueryParams CollisionQueryParams;
		CollisionQueryParams.AddIgnoredActor(this);
		CollisionQueryParams.AddIgnoredActor(GetOwner());

		return GetWorld()->LineTraceSingleByChannel(
			HitResult,
			ViewLocation, EndLocation,
			ECollisionChannel::ECC_GameTraceChannel1,
			CollisionQueryParams
		);
	}
	return false;
}
