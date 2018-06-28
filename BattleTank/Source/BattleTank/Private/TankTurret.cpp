// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"



void UTankTurret::Rotate( float relativeSpeed )
{
	relativeSpeed = FMath::Clamp( relativeSpeed, -1.f, 1.f );

	auto rotationChange = relativeSpeed * maxDegreesPerSeconds * GetWorld()->DeltaTimeSeconds;
	auto newRotation = RelativeRotation.Yaw + rotationChange;

	SetRelativeRotation( FRotator( 0, newRotation, 0 ));
}
