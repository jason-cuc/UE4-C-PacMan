// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "..\MypacmanGameModeBase.h"
#include "PacManCharacter.generated.h"

UCLASS()
class MYPACMAN_API APacManCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APacManCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	int CollectablesToEeat;
	int Lives;

	void MoveXAxis(float AxisValue);
	void MoveYAxis(float AxisValue);

	void ReStart();

	void NewGame();

	void Pause();

	void Killed();
	UFUNCTION()
	void OnCollision(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult);
private:
	FVector CurrentVelocity;
	AMypacmanGameModeBase* GameMode;
	FVector StartPoint;
};
