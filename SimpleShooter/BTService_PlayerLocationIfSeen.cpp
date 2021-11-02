#include "BTService_PlayerLocationIfSeen.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = "Update Player Location If Seen";
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	constexpr int32 kPlayerIndex = 0;
	if (auto* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), kPlayerIndex))
	{
		if (auto* AIOwner = OwnerComp.GetAIOwner())
		{
			if (AIOwner->LineOfSightTo(PlayerPawn))
			{
				auto PlayerLocation = PlayerPawn->GetActorLocation();
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerLocation);
			}
			else
			{
				OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
			}
		}
	}
}
