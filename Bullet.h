// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class PROGRAMMING_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Variables
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* BulletMesh;

	class UProjectileMovementComponent* BulletMovement;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
