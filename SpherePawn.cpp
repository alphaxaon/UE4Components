// Fill out your copyright notice in the Description page of Project Settings.


#include "SpherePawn.h"
#include "Bullet.h"
#include "Classes/Components/InputComponent.h"
#include "Classes/GameFramework/FloatingPawnMovement.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/Camera/CameraComponent.h"
#include "Classes/GameFramework/SpringArmComponent.h"

// Sets default values
ASpherePawn::ASpherePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Add a movement controller
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));

	// Add a static mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	// Add a spring arm to prevent camera clipping
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(StaticMesh);
	CameraArm->TargetArmLength = 500.f;

	// Add a camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm);

	// Set the root component 
	SetRootComponent(StaticMesh);

	// Inherit the yaw and pitch from the controller
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
}

// Called when the game starts or when spawned
void ASpherePawn::BeginPlay()
{
	Super::BeginPlay();
}

// Handle moving right
void ASpherePawn::MoveForward(float Amount)
{
	FloatingPawnMovement->AddInputVector(GetActorForwardVector() * Amount);
}

// Handle moving left
void ASpherePawn::MoveRight(float Amount)
{
	FloatingPawnMovement->AddInputVector(GetActorRightVector() * Amount);
}

// Handle turning
void ASpherePawn::Turn(float Amount)
{
	AddControllerYawInput(Amount);
}

// Handle looking up or down
void ASpherePawn::LookUp(float Amount)
{
	AddControllerPitchInput(Amount);
}

// Handle shooting
void ASpherePawn::Fire()
{
	if (!BulletClass)
		return;

	// Set spawn parameters
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.bNoFail = true;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = this;

	// Set initial position and rotation
	FTransform BulletTransform;
	BulletTransform.SetLocation(GetActorForwardVector() * 500.f + GetActorLocation());
	BulletTransform.SetRotation(GetActorRotation().Quaternion());
	BulletTransform.SetScale3D(FVector(1.f));

	// Spawn the bullet into the world
	GetWorld()->SpawnActor<ABullet>(BulletClass, BulletTransform, SpawnParams);
}

// Called every frame
void ASpherePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASpherePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind axes from player input to custom functions
	PlayerInputComponent->BindAxis("MoveForward", this, &ASpherePawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASpherePawn::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ASpherePawn::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ASpherePawn::LookUp);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASpherePawn::Fire);
}

