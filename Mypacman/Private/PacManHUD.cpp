// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\PacManHUD.h"
#include "..\MypacmanGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Canvas.h"
#include "..\Public\PacManCharacter.h"
void APacManHUD::DrawHUD()
{
	class AMypacmanGameModeBase* GameMode = Cast<AMypacmanGameModeBase>(UGameplayStatics::GetGameMode(this));
	switch (GameMode->GetCurrentState())
	{
	case EGameState::EMenu:
	{
		DrawText(TEXT("Welcome To PacMan!\n\nN to start a new game\nP to pause the game"), FColor::White, (Canvas->SizeX / 2.0f) - 150.0f, (Canvas->SizeY / 2.0f) - 100.0f, HUDFont);
		break;
	}

	case EGameState::EPlaying:
	{
		APacManCharacter* PacMan = Cast<APacManCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
		if (PacMan)
		{
			FString LiveString = TEXT("Lives:") + FString::FromInt(PacMan->Lives);
			DrawText(LiveString, FColor::Green, 50, 50, HUDFont);

			FString CollectablesToEatString = TEXT("CollectableToEat:") + FString::FromInt(PacMan->CollectablesToEeat);
			DrawText(CollectablesToEatString, FColor::Green, Canvas->SizeX - 150, 50, HUDFont);


		}
		break;
	}
	case EGameState::Epause:
	{
		DrawText(TEXT("P to continue the game"), FColor::White, (Canvas->SizeX / 2.0f) - 150.0f, (Canvas->SizeY / 2.0f) - 100.0f, HUDFont);
		break;
	}
	case EGameState::EGameOver:
	{
		DrawText(TEXT("Game Over!\n\nR for another game"), FColor::White, (Canvas->SizeX / 2.0f) - 150.0f, (Canvas->SizeY / 2.0f) - 100.0f, HUDFont);
		break;
	}
	case EGameState::EWin:
	{
		DrawText(TEXT("You Win!\n\nR for another game"), FColor::White, (Canvas->SizeX / 2.0f) - 150.0f, (Canvas->SizeY / 2.0f) - 100.0f, HUDFont);
		break;
	}
	default:

		break;
	}
}
