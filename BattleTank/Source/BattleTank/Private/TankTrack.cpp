// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	tankRoot = Cast<UStaticMeshComponent>( GetOwner()->GetRootComponent() );
}

void UTankTrack::SetThrottle( float throttle )
{
	auto forceApllied = GetForwardVector() * throttle * trackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation( forceApllied, forceLocation );
}

void UTankTrack::TickComponent( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	// Calculate the slippage speed
	auto slippageSpeed = FVector::DotProduct( GetRightVector(), GetComponentVelocity() );
	// work-out the required acceleration this frame to correct
	auto correctionAcceleration = -slippageSpeed / DeltaTime * GetRightVector();
	// Calculate and apply sideways force (F = m a)

	if( !ensure( tankRoot ) ) { return; }
	auto correctionForce = ( tankRoot->GetMass() * correctionAcceleration ) / 2; // two tracks

	tankRoot->AddForce( correctionForce );
}