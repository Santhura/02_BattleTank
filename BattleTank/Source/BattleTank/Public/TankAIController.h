// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"


/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	
public:
	virtual void BeginPlay() override;
	virtual void Tick( float deltaTime ) override;

protected:

	virtual void SetPawn( APawn* inPawn ) override;

	// How close can the AI tank to the player
	UPROPERTY( EditDefaultsOnly, Category = "Setup") 
	float acceptanceRadius = 5000.f;

private:
	UFUNCTION()
		void OnPossedTankDeath();
};
