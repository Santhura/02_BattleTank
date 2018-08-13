// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

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

	void ApplySidewaysForce( );
	void DrivingTrack();

	UFUNCTION()
	void OnHit( UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult& hit );

	UStaticMeshComponent* tankRoot = nullptr;
	float currentThrottle = 0;

};
