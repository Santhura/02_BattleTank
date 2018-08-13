// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	tankRoot = Cast<UStaticMeshComponent>( GetOwner()->GetRootComponent() );
	OnComponentHit.AddDynamic( this, &UTankTrack::OnHit );

}

void UTankTrack::SetThrottle( float throttle )
{
	currentThrottle = FMath::Clamp<float>( currentThrottle + throttle, -1, 1 );
}

void UTankTrack::DrivingTrack()
{
	auto forceApllied = GetForwardVector() * currentThrottle * trackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>( GetOwner()->GetRootComponent() );
	tankRoot->AddForceAtLocation( forceApllied, forceLocation );
}

void UTankTrack::OnHit( UPrimitiveComponent * hitComponent, AActor * otherActor, UPrimitiveComponent * otherComponent, FVector normalImpulse, const FHitResult & hit )
{
	// Drive the tracks
	DrivingTrack();
	// apply sideways force
	ApplySidewaysForce( );
	// reset throttle
	currentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce()
{
	// Calculate the slippage speed
	auto slippageSpeed = FVector::DotProduct( GetRightVector(), GetComponentVelocity() );
	// work-out the required acceleration this frame to correct
	auto deltaTime = GetWorld()->GetDeltaSeconds();
	auto correctionAcceleration = -slippageSpeed / deltaTime * GetRightVector();

	if( !ensure( tankRoot ) ) { return; }
	// Calculate and apply sideways force (F = m a)
	auto correctionForce = ( tankRoot->GetMass() * correctionAcceleration ) / 2; // two tracks

	tankRoot->AddForce( correctionForce );
}