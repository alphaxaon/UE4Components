// Fill out your copyright notice in the Description page of Project Settings.

#include "Raft.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

// Sets default values
ARaft::ARaft()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Deck
	DeckMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DeckMesh"));
	DeckMesh->SetSimulatePhysics(true);
	DeckMesh->SetMassOverrideInKg(NAME_None, 2000.f);
	SetRootComponent(DeckMesh);

	// 1st Engine
	Engine1Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Engine1Mesh"));
	Engine1Mesh->SetSimulatePhysics(true);
	Engine1Mesh->SetMassOverrideInKg(NAME_None, 200.f);
	Engine1Mesh->SetupAttachment(DeckMesh);
	Engine1Mesh->SetRelativeLocation(FVector(400.f, 400.f, -100.f));

	// 2nd Engine
	Engine2Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Engine2Mesh"));
	Engine2Mesh->SetSimulatePhysics(true);
	Engine2Mesh->SetMassOverrideInKg(NAME_None, 200.f);
	Engine2Mesh->SetupAttachment(DeckMesh);
	Engine2Mesh->SetRelativeLocation(FVector(-400.f, 400.f, -100.f));

	// 3rd Engine
	Engine3Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Engine3Mesh"));
	Engine3Mesh->SetSimulatePhysics(true);
	Engine3Mesh->SetMassOverrideInKg(NAME_None, 200.f);
	Engine3Mesh->SetupAttachment(DeckMesh);
	Engine3Mesh->SetRelativeLocation(FVector(400.f, -400.f, -100.f));

	// 4th Engine
	Engine4Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Engine4Mesh"));
	Engine4Mesh->SetSimulatePhysics(true);
	Engine4Mesh->SetMassOverrideInKg(NAME_None, 200.f);
	Engine4Mesh->SetupAttachment(DeckMesh);
	Engine4Mesh->SetRelativeLocation(FVector(-400.f, -400.f, -100.f));

	// Attach the 1st engine
	Engine1Constraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Engine1Constraint"));
	Engine1Constraint->SetupAttachment(DeckMesh);
	Engine1Constraint->SetConstrainedComponents(DeckMesh, NAME_None, Engine1Mesh, NAME_None);
	Engine1Constraint->SetAngularSwing1Limit(ACM_Locked, 0.f);
	Engine1Constraint->SetAngularSwing2Limit(ACM_Locked, 0.f);
	Engine1Constraint->SetAngularTwistLimit(ACM_Locked, 0.f);
	Engine1Constraint->SetDisableCollision(true);

	// Attach the 2nd engine
	Engine2Constraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Engine2Constraint"));
	Engine2Constraint->SetupAttachment(DeckMesh);
	Engine2Constraint->SetConstrainedComponents(DeckMesh, NAME_None, Engine2Mesh, NAME_None);
	Engine2Constraint->SetAngularSwing1Limit(ACM_Locked, 0.f);
	Engine2Constraint->SetAngularSwing2Limit(ACM_Locked, 0.f);
	Engine2Constraint->SetAngularTwistLimit(ACM_Locked, 0.f);
	Engine2Constraint->SetDisableCollision(true);

	// Attach the 3rd engine
	Engine3Constraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Engine3Constraint"));
	Engine3Constraint->SetupAttachment(DeckMesh);
	Engine3Constraint->SetConstrainedComponents(DeckMesh, NAME_None, Engine3Mesh, NAME_None);
	Engine3Constraint->SetAngularSwing1Limit(ACM_Locked, 0.f);
	Engine3Constraint->SetAngularSwing2Limit(ACM_Locked, 0.f);
	Engine3Constraint->SetAngularTwistLimit(ACM_Locked, 0.f);
	Engine3Constraint->SetDisableCollision(true);

	// Attach the 4th engine
	Engine4Constraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Engine4Constraint"));
	Engine4Constraint->SetupAttachment(DeckMesh);
	Engine4Constraint->SetConstrainedComponents(DeckMesh, NAME_None, Engine4Mesh, NAME_None);
	Engine4Constraint->SetAngularSwing1Limit(ACM_Locked, 0.f);
	Engine4Constraint->SetAngularSwing2Limit(ACM_Locked, 0.f);
	Engine4Constraint->SetAngularTwistLimit(ACM_Locked, 0.f);
	Engine4Constraint->SetDisableCollision(true);

	// Thruster Engine

	// Controls
}

// Called when the game starts or when spawned
void ARaft::BeginPlay()
{
	Super::BeginPlay();
}

// Lift off the ground
void ARaft::Lift()
{
	// Figure out up vectors
	FVector Engine1UpVector = Engine1Mesh->GetRelativeTransform().GetRotation().GetUpVector();
	FVector Engine2UpVector = Engine2Mesh->GetRelativeTransform().GetRotation().GetUpVector();
	FVector Engine3UpVector = Engine3Mesh->GetRelativeTransform().GetRotation().GetUpVector();
	FVector Engine4UpVector = Engine4Mesh->GetRelativeTransform().GetRotation().GetUpVector();

	// Get horizontal stabilization
	float XRotation = DeckMesh->GetRelativeTransform().GetRotation().X;
	float YRotation = DeckMesh->GetRelativeTransform().GetRotation().Y;

	// Adjust engine lift to fix unstable platform
	// X negative, add force to engines 1 and 2
	// X positive, add force to engines 3 and 4
	// Y negative, add force to engines 1 and 3
	// Y positive, add force to engines 2 and 4
	float AdjustLift1 = (-XRotation * (500 * FMath::Abs(XRotation))) + ( YRotation * (500 * FMath::Abs(YRotation)));
	float AdjustLift2 = (-XRotation * (500 * FMath::Abs(XRotation))) + (-YRotation * (500 * FMath::Abs(YRotation)));
	float AdjustLift3 = ( XRotation * (500 * FMath::Abs(XRotation))) + ( YRotation * (500 * FMath::Abs(YRotation)));
	float AdjustLift4 = ( XRotation * (500 * FMath::Abs(XRotation))) + (-YRotation * (500 * FMath::Abs(YRotation)));

	// Figure out engine forces
	float Lift1 = BaseLift + AdjustLift1;
	float Lift2 = BaseLift + AdjustLift2;
	float Lift3 = BaseLift + AdjustLift3;
	float Lift4 = BaseLift + AdjustLift4;
	if (Lift1 < 0) Lift1 = 0.f;
	if (Lift2 < 0) Lift2 = 0.f;
	if (Lift3 < 0) Lift3 = 0.f;
	if (Lift4 < 0) Lift4 = 0.f;
	FVector Engine1Force = Engine1UpVector * 100000 * Lift1;
	FVector Engine2Force = Engine2UpVector * 100000 * Lift2;
	FVector Engine3Force = Engine3UpVector * 100000 * Lift3;
	FVector Engine4Force = Engine4UpVector * 100000 * Lift4;

	// Add forces at each of the engines
	Engine1Mesh->AddForceAtLocationLocal(Engine1Force, Engine1UpVector);
	Engine2Mesh->AddForceAtLocationLocal(Engine2Force, Engine2UpVector);
	Engine3Mesh->AddForceAtLocationLocal(Engine3Force, Engine3UpVector);
	Engine4Mesh->AddForceAtLocationLocal(Engine4Force, Engine4UpVector);

	// Debug messages
	GEngine->AddOnScreenDebugMessage(-1, 0.005f, FColor::White, FString::Printf(TEXT("X Rotation: %f"), XRotation));
	GEngine->AddOnScreenDebugMessage(-1, 0.005f, FColor::White, FString::Printf(TEXT("Y Rotation: %f"), YRotation));
	GEngine->AddOnScreenDebugMessage(-1, 0.005f, FColor::White, TEXT("   "));
	GEngine->AddOnScreenDebugMessage(-1, 0.005f, FColor::White, FString::Printf(TEXT("Engine 1: %f"), Engine1Force.Z / 450000.f));
	GEngine->AddOnScreenDebugMessage(-1, 0.005f, FColor::White, FString::Printf(TEXT("Engine 2: %f"), Engine2Force.Z / 450000.f));
	GEngine->AddOnScreenDebugMessage(-1, 0.005f, FColor::White, FString::Printf(TEXT("Engine 3: %f"), Engine3Force.Z / 450000.f));
	GEngine->AddOnScreenDebugMessage(-1, 0.005f, FColor::White, FString::Printf(TEXT("Engine 4: %f"), Engine4Force.Z / 450000.f));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Engine 4: " + LiftEngine4Mesh->GetRelativeTransform().GetLocation().ToString()));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("Base Lift Force: %f"), BaseLift));
}

// Called every frame
void ARaft::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ARaft::Lift();
}

