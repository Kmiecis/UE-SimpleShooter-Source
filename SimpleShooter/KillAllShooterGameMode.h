#pragma once

#include "CoreMinimal.h"
#include "SimpleShooterGameModeBase.h"
#include "KillAllShooterGameMode.generated.h"

UCLASS()
class SIMPLESHOOTER_API AKillAllShooterGameMode : public ASimpleShooterGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PawnKilled(APawn* PawnKilled) override;
};
