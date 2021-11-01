#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AShooterCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

protected:
	virtual void BeginPlay() override;

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Shoot();

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;
	UPROPERTY()
	AGun* Gun;
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.0f;
	UPROPERTY(VisibleAnywhere)
	float Health = 0.0f;
};
