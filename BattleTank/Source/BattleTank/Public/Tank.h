// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// forward Declaration
class UTankBarrel;
class UTankAimingComponent;
class UTankTurret;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* tankAimingComponent = nullptr;
	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* tankMovementComponent = nullptr;

public:	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void BarrelReference( UTankBarrel * barrelToSet );

	UFUNCTION( BlueprintCallable, Category = Setup )
	void TurretReference( UTankTurret* turretToSet );

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	void AimAt( FVector hitLocation );

private:
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY( EditDefaultsOnly, Category = Setup )
	TSubclassOf<AProjectile> projecttileBlueprint;

	UPROPERTY( EditAnywhere, Category = Firing )
	float launchSpeed = 5000;
	UPROPERTY( EditDefaultsOnly, Category = Firing )
	float reloadTimeInSeconds = 3.f;

	// Local barrel reference for spawning projectile
	UTankBarrel* barrel = nullptr;

	double lastFireTime = 0;
};
