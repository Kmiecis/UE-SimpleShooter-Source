#include "ShooterAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
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
