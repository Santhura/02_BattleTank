// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialise( UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet )
{
	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove( const FVector & MoveVelocity, bool bForceMaxSpeed )
{
	// No need to call super as we're replacing the functionality

	auto tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto forwardThrow = FVector::DotProduct( tankForward, AIForwardIntention );
	IntendMoveForward( forwardThrow );

	auto rightThrow = FVector::CrossProduct( tankForward, AIForwardIntention ).Z;
	IntendTurnRight( rightThrow );
}

void UTankMovementComponent::IntendMoveForward( float Throw )
{
	if( !leftTrack || !rightTrack ) { return; }
	leftTrack->SetThrottle( Throw );
	rightTrack->SetThrottle( Throw );
}

void UTankMovementComponent::IntendTurnRight( float Throw )
{
	if( !leftTrack || !rightTrack ) { return; }
	leftTrack->SetThrottle( Throw );
	rightTrack->SetThrottle( -Throw );
}