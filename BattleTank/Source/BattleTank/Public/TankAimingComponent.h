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
class AProjectile;

// hold barrel's properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION( BlueprintCallable, Category = "Setup" )
	void Initialise( UTankBarrel* barrelToSet, UTankTurret * turretToSet );

public:	
	virtual void BeginPlay() override;
	virtual void TickComponent( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction ) override;

	void AimAt( FVector hitLocation );

	UFUNCTION( BlueprintCallable, Category = "Firing" )
	void Fire();

	EFiringState GetFiringState() const;

protected:
	UPROPERTY( BlueprintReadOnly, Category = "State" )
	EFiringState firingState = EFiringState::Reloading;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();
	void MoveBarrelTowards( FVector aimDirection );
	bool IsBarrelMoving();

	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;

	UPROPERTY( EditDefaultsOnly, Category = "Setup" )
	TSubclassOf<AProjectile> projecttileBlueprint;

	UPROPERTY( EditDefaultsOnly, Category = "Firing" )
	float reloadTimeInSeconds = 3.f;

	double lastFireTime = 0;

	UPROPERTY( EditAnywhere, Category = "Firing" )
	float launchSpeed = 5000;

	FVector aimDirection = FVector( 0 );
};
