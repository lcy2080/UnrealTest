// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawnMovementComponent.h"
#include "Engine.h"

void UMyPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFuction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFuction);

	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::White, TEXT("Tick Update"));

	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::White, TEXT("Skip"));
		return;
	}

	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 150.f;

	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::White, DesiredMovementThisFrame.ToString());
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
		}
	}
}

