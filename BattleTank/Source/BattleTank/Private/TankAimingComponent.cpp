// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::Initialise( UTankBarrel* barrelToSet, UTankTurret * turretToSet )
{
	barrel = barrelToSet;
	turret = turretToSet;
}

UTankBarrel* UTankAimingComponent::GetBarrelReference()
{
	return barrel;
}

void UTankAimingComponent::AimAt( FVector hitLocation, float launchSpeed )
{
	if( !ensure(barrel) ) { return; }
	FVector outLaunchVelocity;
	FVector startLocation = barrel->GetSocketLocation( FName( "Projectile" ) );
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		outLaunchVelocity,
		startLocation,
		hitLocation,
		launchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	// Calculate the outLaunchVelocity
	if( bHaveAimSolution )
	{
		auto aimDireciton = outLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(aimDireciton);
		//auto time = GetWorld()->GetTimeSeconds();
		//UE_LOG( LogTemp, Warning, TEXT( "%f: Aim solution found" ), time);
	}
	else
	{
		//auto time = GetWorld()->GetTimeSeconds();
		//UE_LOG( LogTemp, Warning, TEXT( "%f: No aim solve found" ), time );

	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	if(!ensure( barrel && turret) ) { return; }

	// work-out difference between current barrel rotation, and aimDirection
	auto barrelRotation = barrel->GetForwardVector().Rotation();
	auto aimAsRotator = aimDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotation;

	barrel->Elevate(deltaRotator.Pitch);
	turret->Rotate( deltaRotator.Yaw );
}

