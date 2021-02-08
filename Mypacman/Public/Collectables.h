// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Collectables.generated.h" //只能放在头文件最后面

UCLASS() //宏定义 对类的属性进行设置
class MYPACMAN_API ACollectables : public AActor
{
	GENERATED_BODY() //
	
public:	
	// Sets default values for this actor's properties
	ACollectables();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;  //游戏启动的时候调用

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;   //每一帧都进行调用，参数为帧与帧的时间间隔

	UPROPERTY(VisibleAnywhere, Category = Colletable) //宏改变变量的属性
	UStaticMeshComponent* CollectableMesh;  //控制显示
	UPROPERTY(EditDefaultsOnly, Category = Colletable)
	USphereComponent* BaseCollisionComponent; //控制碰撞
	UPROPERTY(EditAnywhere, Category = Colletable)
	bool bIsSuperCollectable;
};
