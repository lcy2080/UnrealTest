// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawn.h"
#include "Classes/Components/SphereComponent.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/Camera/CameraComponent.h"
#include "Classes/GameFramework/SpringArmComponent.h"
#include "MyPawnMovementComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("RootComp"));
	RootComponent = SphereComp;
	SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual"));
	SphereVisual->SetupAttachment(RootComponent);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->RelativeRotation = FRotator(-45.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 400.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.f;

	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	MovementComp = CreateDefaultSubobject<UMyPawnMovementComponent>(TEXT("MovementComponent"));
	MovementComp->UpdatedComponent = RootComponent;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &AMyPawn::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &AMyPawn::MoveRight);

}

UPawnMovementComponent * AMyPawn::GetMovementComponent() const
{
	return MovementComp;
}

void AMyPawn::MoveForward(float AxisValue)
{
	if (MovementComp && (MovementComp->UpdatedComponent == RootComponent))
	{
		MovementComp->AddInputVector(GetActorForwardVector() * AxisValue);
	}
}

void AMyPawn::MoveRight(float AxisValue)
{
	if (MovementComp && (MovementComp->UpdatedComponent == RootComponent))
	{
		MovementComp->AddInputVector(GetActorRightVector() * AxisValue);
	}
}

