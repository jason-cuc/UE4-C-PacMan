// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Collectables.generated.h" //ֻ�ܷ���ͷ�ļ������

UCLASS() //�궨�� ��������Խ�������
class MYPACMAN_API ACollectables : public AActor
{
	GENERATED_BODY() //
	
public:	
	// Sets default values for this actor's properties
	ACollectables();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;  //��Ϸ������ʱ�����

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;   //ÿһ֡�����е��ã�����Ϊ֡��֡��ʱ����

	UPROPERTY(VisibleAnywhere, Category = Colletable) //��ı����������
	UStaticMeshComponent* CollectableMesh;  //������ʾ
	UPROPERTY(EditDefaultsOnly, Category = Colletable)
	USphereComponent* BaseCollisionComponent; //������ײ
	UPROPERTY(EditAnywhere, Category = Colletable)
	bool bIsSuperCollectable;
};
