// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Classes/Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference( UStaticMeshComponent * barrelToSet )
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
		auto tankName = GetOwner()->GetName();
		//UE_LOG( LogTemp, Warning, TEXT( "%s is Aiming at %s" ), *tankName, *aimDireciton.ToString() );
		MoveBarrelTowards(aimDireciton);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	// work-out difference between current barrel rotation, and aimDirection
	auto barrelRotation = barrel->GetForwardVector().Rotation();
	auto aimAsRotator = aimDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotation;
	UE_LOG( LogTemp, Warning, TEXT( "AimAsRotator: %s" ), *aimAsRotator.ToString()  );

	// move the barrel the right amount this frame


	// given a max elevation speed, and the frame time
}
