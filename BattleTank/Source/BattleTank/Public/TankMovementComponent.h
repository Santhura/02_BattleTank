// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class ATank;
class UTankTrack;

/**
 * Responsible for driving the tank tracks
 */
UCLASS( meta = ( BlueprintSpawnableComponent ) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
		
public:
	UFUNCTION( BlueprintCallable, Category = "Setup" )
	void Initialise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet);

	UFUNCTION( BlueprintCallable, Category = "Input" )
	void IntendMoveForward( float Throw );

	UFUNCTION( BlueprintCallable, Category = "Input" )
	void IntendTurnRight( float Throw );

private:
	// Called from the pathfinding logic by the AI controllers
	virtual void RequestDirectMove( const FVector& MoveVelocity, bool bForceMaxSpeed ) override;

	UTankTrack * leftTrack = nullptr;
	UTankTrack * rightTrack = nullptr;
};
