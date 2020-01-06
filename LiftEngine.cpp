// Fill out your copyright notice in the Description page of Project Settings.

#include "LiftEngine.h"
#include "Classes/Components/StaticMeshComponent.h"

// Sets default values
ALiftEngine::ALiftEngine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Engine
	EngineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EngineMesh"));
	SetRootComponent(EngineMesh);

	// Enable physics
	EngineMesh->SetSimulatePhysics(true);
	EngineMesh->SetMassOverrideInKg(NAME_None, 200.f);

	// Thruster effect
	ThrustEffectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ThrustEffectMesh"));
	ThrustEffectMesh->SetupAttachment(EngineMesh);
}

// Called when the game starts or when spawned
void ALiftEngine::BeginPlay()
{
	Super::BeginPlay();
}

// Lift off the ground
void ALiftEngine::Lift()
{
	FVector ForceToAdd = GetActorUpVector() * 100000 * BaseLift;

	EngineMesh->AddForce(ForceToAdd);
}

// Called every frame
void ALiftEngine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ALiftEngine::Lift();
}

