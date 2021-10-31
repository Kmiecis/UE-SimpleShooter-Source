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

	auto* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn)
	{
		auto* OwnerController = OwnerPawn->GetController();
		if (OwnerController)
		{
			FVector ViewLocation;
			FRotator ViewRotation;
			OwnerController->GetPlayerViewPoint(ViewLocation, ViewRotation);

			auto ShotDirection = ViewRotation.Vector();
			auto EndLocation = ViewLocation + ShotDirection * MaxRange;

			FHitResult HitResult;
			bool HitSuccess = GetWorld()->LineTraceSingleByChannel(HitResult, ViewLocation, EndLocation, ECollisionChannel::ECC_GameTraceChannel1);
			if (HitSuccess)
			{
				auto HitPoint = HitResult.ImpactPoint;
				auto HitRotation = (-ShotDirection).Rotation();

				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, HitPoint, HitRotation);
			}
		}
	}
}

void AGun::BeginPlay()
{
	Super::BeginPlay();
}
