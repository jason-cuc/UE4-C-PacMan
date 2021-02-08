// Fill out your copyright notice in the Description page of Project Settings.


//#include "AIEnemy.h"
#include "..\Public\AIEnemy.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void AAIEnemy::OnPossess(class APawn* InPawn) {
	Super::OnPossess(InPawn);
	Bot = Cast<AEnemy>(InPawn);
	HomeLocation = Bot->GetActorLocation();
	SearchNewPoint();
	GameMode = Cast<AMypacmanGameModeBase>(UGameplayStatics::GetGameMode(this));

}

void AAIEnemy::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult & Result)
{
	if (!Bot->bIsDead && GameMode->GetCurrentState()!=EGameState::Epause) {
		SearchNewPoint();
	}
}

void AAIEnemy::SearchNewPoint()
{
	UNavigationSystemV1* NavMesh = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);

	if (NavMesh) {
		const float SearchRadius = 10000.0f;
		FNavLocation RandomPt;

		const bool bFound = NavMesh->GetRandomReachablePointInRadius(Bot->GetActorLocation(), SearchRadius, RandomPt);
		//const bool bFound = NavMesh->GetRandomReachablePointInRadius(myPacMan->GetActorLocation(), SearchRadius, RandomPt);

		if (bFound)
		{
			MoveToLocation(RandomPt);
		}
	}
}

void AAIEnemy::GoHome()
{
	MoveToLocation(HomeLocation);
	GetWorldTimerManager().SetTimer(DeadTime,this,&AAIEnemy::ReArm,5.0f,false);
}

void AAIEnemy::ReArm()
{
	GetWorldTimerManager().ClearTimer(DeadTime);
	Bot->ReArm();
}

void AAIEnemy::StopMove()
{
	//StopMovement();
	MoveToLocation(Bot->GetActorLocation());
}
