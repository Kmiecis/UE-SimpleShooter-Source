#include "BTService_PlayerLocation.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_PlayerLocation::UBTService_PlayerLocation()
{
	NodeName = "Update Player Location";
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	constexpr int32 kPlayerIndex = 0;
	if (auto* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), kPlayerIndex))
	{
		auto PlayerLocation = PlayerPawn->GetActorLocation();
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerLocation);
	}
}
