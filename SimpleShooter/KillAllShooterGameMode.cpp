#include "KillAllShooterGameMode.h"

void AKillAllShooterGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);
	
	if (auto* PlayerController = Cast<APlayerController>(PawnKilled->GetController()))
	{
		PlayerController->GameHasEnded(nullptr, false);
	}
}
