// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise( UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet )
{
	if( !leftTrackToSet || !rightTrackToSet ) { return; }

	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward( float Throw )
{
	UE_LOG( LogTemp, Warning, TEXT( "Intend move forward throw: %f" ), Throw );

	leftTrack->SetThrottle( Throw );
	rightTrack->SetThrottle( Throw );
	//TODO prevent double speed due to dual control
}
