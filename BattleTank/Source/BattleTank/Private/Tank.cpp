// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// no need to pretect points as added at construction
	tankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>( FName( "Aiming Component" ) );
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATank::AimAt( FVector hitLocation )
{
	tankAimingComponent->AimAt( hitLocation, launchSpeed );
}

void ATank::BarrelReference( UTankBarrel * barrelToSet )
{
	tankAimingComponent->SetBarrelReference( barrelToSet );
	barrel = barrelToSet;
}

void ATank::TurretReference( UTankTurret * turretToSet )
{
	tankAimingComponent->SetTurretReference( turretToSet );
}

void ATank::Fire()
{
	if( !barrel ) { return; }

	// spawn projectile at the socket location
	auto projectile = GetWorld()->SpawnActor<AProjectile>( projecttileBlueprint, 
										 barrel->GetSocketLocation(FName("Projectile")),
										 barrel->GetSocketRotation(FName("Projectile")) );


	projectile->LaunchProjectile( launchSpeed );
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

