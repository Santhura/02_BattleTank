// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "TankBarrel.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference( UTankBarrel * barrelToSet )
{
	barrel = barrelToSet;
}


void UTankAimingComponent::AimAt( FVector hitLocation, float launchSpeed )
{
	if( !barrel ) { return; }
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
		auto time = GetWorld()->GetTimeSeconds();
		UE_LOG( LogTemp, Warning, TEXT( "%f: Aim solution found" ), time);
	}
	else
	{
		auto time = GetWorld()->GetTimeSeconds();
		UE_LOG( LogTemp, Warning, TEXT( "%f: No aim solve found" ), time );

	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	// work-out difference between current barrel rotation, and aimDirection
	auto barrelRotation = barrel->GetForwardVector().Rotation();
	auto aimAsRotator = aimDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotation;
	//UE_LOG( LogTemp, Warning, TEXT( "AimAsRotator: %s" ), *aimAsRotator.ToString()  );

	barrel->Elevate(5); // TODO remove magic number
}
