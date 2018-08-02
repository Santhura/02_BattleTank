// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}


void ATankAIController::Tick( float deltaTime )
{
	Super::Tick( deltaTime );

	auto controlledTank = Cast<ATank>( GetPawn() );
	auto playerTank = Cast<ATank>( GetWorld()->GetFirstPlayerController()->GetPawn());

	if( ensure( playerTank ))
	{
		// move towards the player
		MoveToActor( playerTank, acceptanceRadius );

		// aim towards the player
		controlledTank->AimAt( playerTank->GetActorLocation() );

		// fire if ready
		controlledTank->Fire(); // TODO limit firing rate
	}
}

