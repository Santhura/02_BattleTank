// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AimAt( FVector hitLocation );

	UFUNCTION(BlueprintCallable, Category = Setup)
	void BarrelReference( UStaticMeshComponent * barrelToSet );

private:
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY( EditAnywhere, Category = Firing )
		float launchSpeed = 100000; // TODO find sensible default
	
};
