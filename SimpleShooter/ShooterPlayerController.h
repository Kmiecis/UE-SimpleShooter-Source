#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void GameHasEnded(AActor* EndGameFocus, bool bIsWinner) override;

protected:
	virtual void BeginPlay() override;

private:
	FTimerHandle RestartTimer;
	
private:
	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.0f;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDScreenClass;
	UPROPERTY()
	UUserWidget* HUDScreen;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreenClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinScreenClass;
};
