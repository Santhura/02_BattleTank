// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialise( UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet )
{
	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward( float Throw )
{
	if( !leftTrack || !rightTrack ) { return; }
	leftTrack->SetThrottle( Throw );
	rightTrack->SetThrottle( Throw );
	//TODO prevent double speed due to dual control
}

void UTankMovementComponent::IntendTurnRight( float Throw )
{
	if( !leftTrack || !rightTrack ) { return; }
	leftTrack->SetThrottle( Throw );
	rightTrack->SetThrottle( -Throw );
	//TODO prevent double speed due to dual control
}
