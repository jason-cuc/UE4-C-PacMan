// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "..\Public\Enemy.h"
#include "..\MypacmanGameModeBase.h"
#include "..\Public\PacManCharacter.h"
#include "AIEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MYPACMAN_API AAIEnemy : public AAIController
{
	GENERATED_BODY()
	
public:
	void OnPossess(class APawn* InPawn) override; //==beginplay
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;//ÒÆ¶¯Í£Ö¹×öÊ²Ã´

	void SearchNewPoint();

	void GoHome();
	void ReArm();//
	void StopMove();


private:
	class AEnemy* Bot;
	FVector HomeLocation;
	FTimerHandle DeadTime;
	AMypacmanGameModeBase* GameMode;
	class APacManCharacter* myPacMan;
};
