// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto playerTank = GetPlayerTank();
	PrintTank( playerTank, true );
}


void ATankAIController::Tick( float deltaTime )
{
	Super::Tick( deltaTime );
	if( GetPlayerTank() )
	{
		// aim towards the player
		GetControlledTank()->AimAt( GetPlayerTank()->GetActorLocation() );
	}
}

ATank *ATankAIController::GetControlledTank() const
{
	return Cast<ATank>( GetPawn() );
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if( !playerPawn ) { return nullptr; }
	return Cast<ATank>(playerPawn);
}

void ATankAIController::PrintTank( ATank* controller, bool isPlayer ) const
{
	FString tankController = ( isPlayer ) ? "Player " : "AI ";

	if( !controller )
	{
		UE_LOG( LogTemp, Warning, TEXT( "%s constoller can't find player tank" ), *tankController );
	}
	else
	{
		UE_LOG( LogTemp, Warning, TEXT( "%s controller found player: %s" ),  *tankController, *controller->GetName() );
	}
}
