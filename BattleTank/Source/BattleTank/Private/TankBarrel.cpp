// Fill out your copyright notice in the Description page of Project Settings.
#include "Engine/World.h"
#include "TankBarrel.h"



void UTankBarrel::Elevate( float relativeSpeed )
{
	// move the barrel the right amount this frame
	// given a max elevation speed, and the frame time
	relativeSpeed = FMath::Clamp( relativeSpeed, -1.f, 1.f );

	auto elevationChange = relativeSpeed * maxDegreesPerSeconds * GetWorld()->DeltaTimeSeconds;
	auto rawNewElevation = RelativeRotation.Pitch + elevationChange;
	auto elevation = FMath::Clamp( rawNewElevation, minElevationDegrees, maxElevationDegrees );

	SetRelativeRotation( FRotator( elevation, 0, 0 ) );
}
