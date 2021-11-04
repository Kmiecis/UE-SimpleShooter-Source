#include "ShooterPlayerController.h"

#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUDScreen = CreateWidget(this, HUDScreenClass);
	if (HUDScreen)
	{
		HUDScreen->AddToViewport();
	}
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	HUDScreen->RemoveFromViewport();

	if (bIsWinner)
	{
		if (auto* WinScreen = CreateWidget(this, WinScreenClass))
		{
			WinScreen->AddToViewport();
		}
	}
	else
	{
		if (auto* LoseScreen = CreateWidget(this, LoseScreenClass))
		{
			LoseScreen->AddToViewport();
		}
	}

	GetWorld()->GetTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
