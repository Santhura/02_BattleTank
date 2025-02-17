// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FTankDelegate );

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

	// Called by the engine when actor damage is dealt
	virtual float TakeDamage( float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser ) override;

	// returns current health as a percentage of starting healthf, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;
	UFUNCTION( )
	float GetCurrentHealth() const;

	FTankDelegate OnDeath;

protected:
	UPROPERTY( EditDefaultsOnly, Category = "Setup" )
	int32 startingHealth = 100;

	UPROPERTY( VisibleAnywhere, Category = "Health" )
	int32 currentHealth;
};
