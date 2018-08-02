// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Engine/World.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}


void ATank::BeginPlay()
{
	Super::BeginPlay(); // needed for BP beginplay!
}


void ATank::Fire()
{
	if( !ensure( barrel ) ) { return; }

	bool isReloaded = ( FPlatformTime::Seconds() - lastFireTime ) > reloadTimeInSeconds;
	if(isReloaded )
	{
		// spawn projectile at the socket location
		auto projectile = GetWorld()->SpawnActor<AProjectile>( projecttileBlueprint,
															   barrel->GetSocketLocation( FName( "Projectile" ) ),
															   barrel->GetSocketRotation( FName( "Projectile" ) ) );
		projectile->LaunchProjectile( 5000 );
		lastFireTime = FPlatformTime::Seconds();
	}
}