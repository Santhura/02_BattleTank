// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	tankRoot = Cast<UStaticMeshComponent>( GetOwner()->GetRootComponent() );

}

void UTankTrack::SetThrottle( float throttle )
{
	float currentThrottle = FMath::Clamp<float>( throttle, -1, 1 );
	DrivingTrack( currentThrottle );
}

void UTankTrack::DrivingTrack( float currentThrottle )
{
	auto forceApllied = currentThrottle * trackMaxDrivingForce;
	auto wheels = GetWheels();
	auto forcePerWheel = forceApllied / wheels.Num();

	for( ASprungWheel* wheel : wheels )
	{
		wheel->AddDrivingForce( forcePerWheel );
	}
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> resultArray;
	TArray<USceneComponent*> children;
	GetChildrenComponents( true, children );

	for( USceneComponent* child : children )
	{
		auto spawnPointChild = Cast<USpawnPoint>( child );
		if( !spawnPointChild ) continue;

		AActor* spawnedChild = spawnPointChild->GetSpawnedActor();
		auto sprungWheel = Cast<ASprungWheel>( spawnedChild );
		if( !sprungWheel ) continue;

		resultArray.Add( sprungWheel );
	}

	return resultArray;
}