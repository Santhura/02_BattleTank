// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

class ASprungWheel;

/**
 * TankTrack is used to set maximum driving force, and to apply forces to the tank.
 */
UCLASS( meta = ( BlueprintSpawnableComponent ))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle( float throttle );

	// Max force per track in Newtons
	UPROPERTY( EditDefaultsOnly, Category = "Setup" )
		float trackMaxDrivingForce = 400000; // assume 40 ton tank, and 1g acceleration

	virtual void BeginPlay() override;

private:
	UTankTrack();

	TArray<ASprungWheel*> GetWheels() const;

	void DrivingTrack( float currentThrottle);

	UStaticMeshComponent* tankRoot = nullptr;
	

};
