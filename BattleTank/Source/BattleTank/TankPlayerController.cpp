// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Camera/PlayerCameraManager.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto aimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if( aimingComponent )
	{
		FoundAimingComponent( aimingComponent );
	}
	else
	{
		UE_LOG( LogTemp, Warning, TEXT( "Player controller can't find aiming component at begin play" ) );
	}
}


void ATankPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	AimTowardsCrosshair();
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>( GetPawn() );
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if( !GetControlledTank() ) { return; }

	FVector hitLocation; // out parameter
	if( GetSightRayHitLocation( hitLocation ) )
	{
		GetControlledTank()->AimAt( hitLocation );
	}
}

bool ATankPlayerController::GetSightRayHitLocation( FVector & outHitLocation ) const
{
	// Find the crosshair position in pixel coordinates
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize( viewportSizeX, viewportSizeY );
	auto screenLocation = FVector2D( viewportSizeX * crossHairXLocation, viewportSizeY * crossHairYLocation );

	// "De-project" the screen position of the crosshair to a world direction

	FVector lookDirection;
	if( GetLookDirection( screenLocation, lookDirection ) )
	{
		// line-trace along that look direction, and see what we hit (up to max range)
		if( GetLookVectorHitLocation( lookDirection, outHitLocation ) )
		{
		}
	}

	return true;
}

bool ATankPlayerController::GetLookDirection( FVector2D screenLocation, FVector & lookDirection ) const
{
	FVector cameraWorldLocation; // to be discarded
	return DeprojectScreenPositionToWorld( 
		screenLocation.X, 
		screenLocation.Y, 
		cameraWorldLocation, 
		lookDirection );
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector lookDirection, FVector& hitLocation) const
{
	FHitResult hit;
	auto startLocation = PlayerCameraManager->GetCameraLocation();
	auto endLocation = startLocation + (lookDirection * lineTraceRange);
	if( GetWorld()->LineTraceSingleByChannel( 
		hit, 
		startLocation, 
		endLocation, 
		ECollisionChannel::ECC_Visibility ) )
	{
		hitLocation = hit.Location;
		return true;
	}
	hitLocation = FVector( 0 );
	return false;
}

