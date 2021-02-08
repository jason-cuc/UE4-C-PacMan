// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PacManHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYPACMAN_API APacManHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category = HUDFont)
	UFont* HUDFont;

	virtual void DrawHUD() override; //每一帧都会调用一次
};
