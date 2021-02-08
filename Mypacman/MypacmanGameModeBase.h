// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
//#include "PacManCharacter.h"
#include "MypacmanGameModeBase.generated.h"

/**
 * 
 */
enum class EGameState :short {
	EMenu,
	EPlaying,
	Epause,
	EGameOver,
	EWin
};
UCLASS()
class MYPACMAN_API AMypacmanGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	EGameState GetCurrentState() const;

	void SetCurrentState(EGameState value);

	void SetEnemyVulnerable();

private:
	EGameState currentState;
	TArray<class AEnemy*> Enemys;
};

FORCEINLINE EGameState AMypacmanGameModeBase::GetCurrentState() const { return currentState; };