#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()

public:
	AGun();
	virtual void Tick(float DeltaTime) override;
	void PullTrigger();

private:
	AController* GetOwnerController() const;
	bool GunTrace(FHitResult& HitResult, FVector& ShotDirection);

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleEffect;
	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;
	UPROPERTY(EditAnywhere)
	UParticleSystem* HitEffect;
	UPROPERTY(EditAnywhere)
	USoundBase* HitSound;
	UPROPERTY(EditAnywhere)
	float MaxRange = 9999.9f;
	UPROPERTY(EditAnywhere)
	float Damage = 10.0f;
};
