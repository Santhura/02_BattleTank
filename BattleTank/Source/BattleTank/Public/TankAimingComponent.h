// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

// forward declaration
class UTankBarrel; 
class UTankTurret;

// hold barrel's properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference( UTankBarrel * barrelToSet );
	void SetTurretReference( UTankTurret* turretToSet );

public:	
	void AimAt( FVector hitLocation, float launchSpeed );


protected:
	UPROPERTY( BlueprintReadOnly, Category = "State" )
		EFiringState firingState = EFiringState::Aiming;

private:
	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;

	void MoveBarrelTowards(FVector aimDirection);
};
