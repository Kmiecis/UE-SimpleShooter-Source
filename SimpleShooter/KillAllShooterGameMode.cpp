#include "KillAllShooterGameMode.h"

#include "EngineUtils.h"
#include "ShooterAIController.h"

void AKillAllShooterGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);
	
	if (auto* PlayerController = Cast<APlayerController>(PawnKilled->GetController()))
	{
		EndGame(false);
	}

	for (auto* Controller : TActorRange<AShooterAIController>(GetWorld()))
	{
		if (!Controller->IsDead())
		{
			return;
		}
	}
	EndGame(true);
}

void AKillAllShooterGameMode::EndGame(bool IsPlayerWinner)
{
	for (auto* Controller : TActorRange<AController>(GetWorld()))
	{
		bool IsWinner = Controller->IsPlayerController() == IsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), IsWinner);
	}
}
