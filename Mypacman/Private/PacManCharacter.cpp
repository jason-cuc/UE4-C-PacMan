// Fill out your copyright notice in the Description page of Project Settings.


//#include "PacManCharacter.h"
#include "..\Public\PacManCharacter.h"
#include "..\Public\Collectables.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APacManCharacter::APacManCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//CollectablesToEeat = 0;
}

// Called when the game starts or when spawned
void APacManCharacter::BeginPlay()
{
	Super::BeginPlay();

	Lives = 3;

	StartPoint = GetActorLocation(); 
	//UE_LOG(LogTemp, Warning, TEXT("StartPoint: %s"), *StartPoint.ToString());
	//获取gamemode
	GameMode =Cast<AMypacmanGameModeBase> (UGameplayStatics::GetGameMode(this));
	//获取碰撞体
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APacManCharacter::OnCollision);
	//遍历场景得到个数
	for (TActorIterator<ACollectables> CollectablesIter(GetWorld()); CollectablesIter; ++CollectablesIter)
	{
		++CollectablesToEeat;
	}
	//UE_LOG(LogTemp, Warning, TEXT("Total Collectables is %d"), CollectablesToEeat);
	
}

// Called every frame
void APacManCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APacManCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAxis("MoveX", this, &APacManCharacter::MoveXAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &APacManCharacter::MoveYAxis);
	PlayerInputComponent->BindAction("Pause",IE_Pressed, this, &APacManCharacter::Pause);
	PlayerInputComponent->BindAction("ReStart", IE_Pressed, this, &APacManCharacter::ReStart);
	PlayerInputComponent->BindAction("NewGame", IE_Pressed, this, &APacManCharacter::NewGame);

}

void APacManCharacter::MoveXAxis(float AxisValue)
{
	if (GameMode->GetCurrentState() == EGameState::EPlaying)
	{
		CurrentVelocity.X = AxisValue;
		AddMovementInput(CurrentVelocity);
	}
}

void APacManCharacter::MoveYAxis(float AxisValue)
{
	if (GameMode->GetCurrentState() == EGameState::EPlaying)
	{
		CurrentVelocity.Y = AxisValue;
		AddMovementInput(CurrentVelocity);
	}
}

void APacManCharacter::ReStart()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("RestartLevel"));
}

void APacManCharacter::NewGame()
{
	if (GameMode->GetCurrentState() == EGameState::EMenu)
	{
		GameMode->SetCurrentState(EGameState::EPlaying);
	}
}

void APacManCharacter::Pause()
{
	if (GameMode->GetCurrentState() == EGameState::EPlaying)
	{
		GameMode->SetCurrentState(EGameState::Epause);
	}
	else if (GameMode->GetCurrentState() == EGameState::Epause)
	{
		GameMode->SetCurrentState(EGameState::EPlaying);
	}
}

void APacManCharacter::Killed()
{
	if (--Lives == 0)
	{
		GameMode->SetCurrentState(EGameState::EGameOver);
	}
	else
	{
		SetActorLocation(StartPoint);
	}
}

void APacManCharacter::OnCollision(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (GameMode->GetCurrentState() == EGameState::EPlaying)
	{
		if (OtherActor->IsA(ACollectables::StaticClass())) {
			ACollectables* collectable = Cast<ACollectables>(OtherActor);
			if (collectable->bIsSuperCollectable)
			{
				GameMode->SetEnemyVulnerable(); 
			}
			OtherActor->Destroy();
			if (--CollectablesToEeat == 0)
			{
				GameMode->SetCurrentState(EGameState::EWin);
			}
			UE_LOG(LogTemp, Warning, TEXT("Remain Collectables is %d"), CollectablesToEeat);
		}
	}
}

