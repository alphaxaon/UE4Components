// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LiftEngine.generated.h"

UCLASS()
class PROGRAMMING_API ALiftEngine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALiftEngine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Functions
	void Lift();

	// Variables
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* EngineMesh;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* ThrustEffectMesh;

	UPROPERTY(EditAnywhere)
	float BaseLift = 1.98f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
