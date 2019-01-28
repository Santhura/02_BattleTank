// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// So that first fire is after initial reload
	lastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialise( UTankBarrel* barrelToSet, UTankTurret * turretToSet )
{
	barrel = barrelToSet;
	turret = turretToSet;
}

void UTankAimingComponent::TickComponent( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction )
{
	if( ammoAmount <= 0 )
	{
		firingState = EFiringState::Empty;
	}
	else if( ( FPlatformTime::Seconds() - lastFireTime ) < reloadTimeInSeconds )
	{
		firingState = EFiringState::Reloading;
	}
	else if( IsBarrelMoving() )
	{
		firingState = EFiringState::Aiming;
	}
	else
	{
		firingState = EFiringState::Locked;
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return firingState;
}

int32 UTankAimingComponent::GetAmmoAmount() const
{
	return ammoAmount;
}

void UTankAimingComponent::AimAt( FVector hitLocation)
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
		aimDirection = outLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(aimDirection);
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

	if( FMath::Abs(deltaRotator.Yaw ) > 180)
		deltaRotator.Yaw = -deltaRotator.Yaw;

	turret->Rotate( deltaRotator.Yaw );
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if( !ensure( barrel ) ) { return false; }
	auto barrelForward = barrel->GetForwardVector();
	return !barrelForward.Equals(aimDirection, 0.01f);
}

void UTankAimingComponent::Fire()
{
	if( firingState == EFiringState::Locked || firingState == EFiringState::Aiming )
	{
		// spawn projectile at the socket location
		if( !ensure( barrel ) ) { return; }
		if( !ensure( projecttileBlueprint ) ) { return; }
		auto projectile = GetWorld()->SpawnActor<AProjectile>( projecttileBlueprint,
															   barrel->GetSocketLocation( FName( "Projectile" ) ),
															   barrel->GetSocketRotation( FName( "Projectile" ) ) );
		projectile->LaunchProjectile( launchSpeed );
		lastFireTime = FPlatformTime::Seconds();
		ammoAmount--;
	}
}


