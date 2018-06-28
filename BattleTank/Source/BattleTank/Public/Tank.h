// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// forward Declaration
class UTankBarrel;
class UTankAimingComponent;
class UTankTurret;

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

public:	

	void AimAt( FVector hitLocation );

	UFUNCTION(BlueprintCallable, Category = Setup)
	void BarrelReference( UTankBarrel * barrelToSet );

	UFUNCTION( BlueprintCallable, Category = Setup )
	void TurretReference( UTankTurret* turretToSet );

private:
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY( EditAnywhere, Category = Firing )
		float launchSpeed = 5000; // TODO find sensible default
	
};
