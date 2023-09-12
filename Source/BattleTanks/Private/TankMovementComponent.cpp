// Fill out your copyright notice in the Description page of Project Settings.

#include"TankTrack.h"
#include "TankMovementComponent.h"
#include <VisualLogger/VisualLogger.h>

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendMoveRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto MoveDirection = MoveVelocity.GetSafeNormal();

	//UE_LOG(LogTemp, Warning, TEXT("%s Move Direction"), *MoveDirection.ToString());
	//UE_VLOG(this, LogTemp, Warning, TEXT("%s Move Direction"), *MoveDirection.ToString());
	auto ForwardThrow = FVector::DotProduct(TankForward, MoveDirection);
	IntendMoveForward(ForwardThrow);

	auto RightThrow = FVector::CrossProduct(TankForward, MoveDirection).Z;
	IntendMoveRight(RightThrow);
}

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}