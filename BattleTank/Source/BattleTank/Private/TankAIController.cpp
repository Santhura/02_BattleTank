// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick( float deltaTime )
{
	Super::Tick( deltaTime );

	auto controlledTank =  GetPawn();
	auto playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if( !ensure( playerTank && playerTank ) ) { return; }
	
	// move towards the player
	MoveToActor( playerTank, acceptanceRadius );

	// aim towards the player
	auto aimingComp = controlledTank->FindComponentByClass<UTankAimingComponent>();
	aimingComp->AimAt( playerTank->GetActorLocation() );

	// fire if ready
	if( aimingComp->GetFiringState() == EFiringState::Locked )
	{
		aimingComp->Fire();
	}
}