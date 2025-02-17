// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS( meta = ( BlueprintSpawnableComponent ), hidecategories = ( "Collision" ) )
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max rotation speed, and +1 is max up speed
	void Rotate( float relativeSpeed );
	
private:
	UPROPERTY( EditDefaultsOnly, Category = "Setup" )
		float maxDegreesPerSeconds = 35;
	
};
