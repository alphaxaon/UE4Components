// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Raft.generated.h"

UCLASS()
class PROGRAMMING_API ARaft : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARaft();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Functions
	void Lift();

	// Variables
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* DeckMesh;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Engine1Mesh;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Engine2Mesh;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Engine3Mesh;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Engine4Mesh;

	UPROPERTY(EditAnywhere)
	class UPhysicsConstraintComponent* Engine1Constraint;

	UPROPERTY(EditAnywhere)
	class UPhysicsConstraintComponent* Engine2Constraint;

	UPROPERTY(EditAnywhere)
	class UPhysicsConstraintComponent* Engine3Constraint;

	UPROPERTY(EditAnywhere)
	class UPhysicsConstraintComponent* Engine4Constraint;

	UPROPERTY(EditAnywhere)
	float BaseLift = 1.98f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
