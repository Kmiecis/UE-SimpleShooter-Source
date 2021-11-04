#include "ShooterAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

bool AShooterAIController::IsDead() const
{
	if (auto* ShooterCharacter = Cast<AShooterCharacter>(GetPawn()))
	{
		return ShooterCharacter->IsDead();
	}

	return true;
}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehaviorTree)
	{
		RunBehaviorTree(AIBehaviorTree);

		auto StartLocation = GetPawn()->GetActorLocation();
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), StartLocation);
	}
}
