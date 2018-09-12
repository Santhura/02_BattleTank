// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	currentHealth = startingHealth;
}

float ATank::TakeDamage( float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser )
{
	int32 damagePoints = FPlatformMath::RoundToInt( DamageAmount );
	int32 damageToApply = FMath::Clamp( damagePoints, 0, currentHealth);

	currentHealth -= damageToApply;
	if( currentHealth <= 0 )
	{
		OnDeath.Broadcast();
	}
	return damageToApply;
}

float ATank::GetHealthPercent() const
{
	return (float) currentHealth / (float) startingHealth;
}
