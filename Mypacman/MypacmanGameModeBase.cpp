// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "MypacmanGameModeBase.h"
#include "Public/Enemy.h"
#include "EngineUtils.h"

void AMypacmanGameModeBase::SetCurrentState(EGameState value)
{
	currentState = value;
	switch (value)
	{
	case EGameState::EPlaying:
		for (auto Iter(Enemys.CreateIterator()); Iter; ++Iter)
		{
			(*Iter)->SetMove(true);
		}
		break;
	case EGameState::Epause:
		for (auto Iter(Enemys.CreateIterator()); Iter; ++Iter)
		{
			(*Iter)->SetMove(false);
		}
		break;
	case EGameState::EGameOver:
		for (auto Iter(Enemys.CreateIterator()); Iter; ++Iter)
		{
			(*Iter)->Destroy();
		}
		break;
	case EGameState::EWin:
		for (auto Iter(Enemys.CreateIterator()); Iter; ++Iter)
		{
			(*Iter)->Destroy();
		}
		break;
	default:

		break;
	}
}
void AMypacmanGameModeBase::SetEnemyVulnerable()
{
	for (auto Iter(Enemys.CreateIterator()); Iter; ++Iter)
	{
		(*Iter)->SetVulnerable();
	}
}
void AMypacmanGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SetCurrentState(EGameState::EMenu);

	for (TActorIterator<AEnemy> enemyIter(GetWorld()); enemyIter; ++enemyIter)
	{
		AEnemy* enemy = Cast<AEnemy>(*enemyIter);
		if (enemy)
		{
			Enemys.Add(enemy);
		}
	}

}
