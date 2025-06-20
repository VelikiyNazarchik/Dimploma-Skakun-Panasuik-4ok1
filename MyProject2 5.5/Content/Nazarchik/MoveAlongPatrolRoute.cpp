#include "MoveAlongPatrolRoute.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "YourPatrolRouteComponent.h" 

UMoveAlongPatrolRoute::UMoveAlongPatrolRoute()
{
    NodeName = "Patrol";
    bNotifyTick = false;
    bNotifyTaskFinished = true;
    bCreateNodeInstance = true;
}

EBTNodeResult::Type UMoveAlongPatrolRoute::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    CachedController = OwnerComp.GetAIOwner();
    CachedPawn = CachedController ? CachedController->GetPawn() : nullptr;

    if (!CachedController || !CachedPawn) return EBTNodeResult::Failed;

    if (UYourPatrolRouteComponent* PatrolRoute = CachedPawn->FindComponentByClass<UYourPatrolRouteComponent>())
    {
        int32 Index = PatrolRoute->GetCurrentIndex();
        FVector TargetLocation = PatrolRoute->GetSpline()->GetLocationAtSplinePoint(Index, ESplineCoordinateSpace::World);

        FNavPathSharedPtr NavPath;
        CachedController->MoveToLocation(TargetLocation, 100.f, false, true, true, false, 0, true);

        CachedController->ReceiveMoveCompleted.AddDynamic(this, &UMoveAlongPatrolRoute::OnMoveCompleted);
        return EBTNodeResult::InProgress;
    }

    return EBTNodeResult::Failed;
}

void UMoveAlongPatrolRoute::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    if (CachedPawn)
    {
        if (UYourPatrolRouteComponent* PatrolRoute = CachedPawn->FindComponentByClass<UYourPatrolRouteComponent>())
        {
            PatrolRoute->IncrementPatrolIndex();
        }
    }

    FinishLatentTask(*CachedController->GetBrainComponent(), EBTNodeResult::Succeeded);
}

EBTNodeResult::Type UMoveAlongPatrolRoute::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (CachedController)
    {
        CachedController->StopMovement();
    }

    return EBTNodeResult::Aborted;
}
