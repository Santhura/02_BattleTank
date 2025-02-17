// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if( ensure( aimingComponent) )
	{
		FoundAimingComponent( aimingComponent );
	}
}


void ATankPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	auto currentHealth = Cast<ATank>(GetPawn())->GetCurrentHealth();
	if(currentHealth  > 0 )
	{
		AimTowardsCrosshair();
	}
}


void ATankPlayerController::SetPawn( APawn * inPawn )
{
	Super::SetPawn( inPawn );
	if( inPawn )
	{
		auto possessedTank = Cast<ATank>( inPawn );
		if( !ensure( possessedTank ) ) { return; }

		possessedTank->OnDeath.AddUniqueDynamic( this, &ATankPlayerController::OnPossessedTankDeath );
	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	StartSpectatingOnly();
}


void ATankPlayerController::AimTowardsCrosshair()
{
	
	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if( !ensure( aimingComponent ) ) { return; }

	FVector hitLocation; // out parameter
	bool bGotHitLocation = GetSightRayHitLocation( hitLocation );
	if(bGotHitLocation )
	{
		aimingComponent->AimAt( hitLocation );
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
		return GetLookVectorHitLocation( lookDirection, outHitLocation );
		
	}

	return false;
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
		ECollisionChannel::ECC_Camera ) )
	{
		hitLocation = hit.Location;
		return true;
	}
	hitLocation = FVector( 0 );
	return false;
}


