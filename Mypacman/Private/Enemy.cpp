// Fill out your copyright notice in the Description page of Project Settings.


//#include "Enemy.h"
#include "..\Public\Enemy.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
//#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "..\Public\AIEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyBody = CreateDefaultSubobject<UStaticMeshComponent> (TEXT("Body"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderObj(TEXT("'/Game/StarterContent/Shapes/Shape_Cylinder'"));

	if (CylinderObj.Succeeded())
	{
		EnemyBody->SetStaticMesh(CylinderObj.Object);
	}

	EnemyBody->SetWorldScale3D(FVector(0.7f, 0.7f, 1.0f));
	EnemyBody->SetRelativeLocation(FVector(0, 0, -50.0f));
	EnemyBody->SetupAttachment(RootComponent);

	GetCapsuleComponent()->SetCapsuleRadius(40.0f);
	GetCapsuleComponent()->SetCapsuleHalfHeight(50.0f);

	static ConstructorHelpers::FObjectFinder<UMaterial> VulnerableMat(TEXT("Material'/Game/Materials/M_Enemy_Vulnerable.M_Enemy_Vulnerable'"));

	if (VulnerableMat.Succeeded())
	{
		VulnerableMaterial = Cast<UMaterialInterface>(VulnerableMat.Object);
	}
	//BaseCollisionComponent->SetSphereRadius(16);

	SetActorEnableCollision(true);
	AIControllerClass = AAIEnemy::StaticClass();
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	DefaultMaterial = EnemyBody->GetMaterial(0);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnCollision);
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
	//VulnerableMaterial
	//VulnerableMaterial = EnemyBody->GetMaterial(0, VulnerableMat);
	//SetVulnerable();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::SetVulnerable()
{
	GetWorldTimerManager().SetTimer(TimeVulnerable, this, &AEnemy::SetInVulnerable, 10.0f, false);
	if (bIsVulnerable)
		return;
	bIsVulnerable = true;
	EnemyBody->SetMaterial(0, VulnerableMaterial);

	GetCharacterMovement()->MaxWalkSpeed = 50.0f;
}

void AEnemy::SetInVulnerable()
{

	GetWorldTimerManager().ClearTimer(TimeVulnerable);
	bIsVulnerable = false;
	EnemyBody->SetMaterial(0, DefaultMaterial);
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
}

void AEnemy::SetMove(bool bMoveIt)
{
	AAIEnemy* AI = Cast<AAIEnemy>(GetController());
	if (bMoveIt)
	{
		AI->SearchNewPoint();
	}
	else {
		AI->StopMove();
	}
}

void AEnemy::Killed()
{
	if (bIsDead) {
		return;
	}
	bIsDead = true;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	AAIEnemy* AI = Cast<AAIEnemy>(GetController());
	AI->GoHome();
}

void AEnemy::ReArm()
{
	bIsDead = false;
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
	if (bIsVulnerable) {
		SetInVulnerable();
	}
	SetMove(true);
}
void AEnemy::OnCollision(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA(APacManCharacter::StaticClass()))
	{
		if (bIsVulnerable) {
			Killed();
		}
		else
		{
			APacManCharacter* PacMan = Cast<APacManCharacter>(OtherActor);
			PacMan->Killed();
		}
	}
}

