// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG( LogTemp, Warning, TEXT( "Player controller begin play" ) );
	auto controlledTank = GetControlledTank();
	if( controlledTank )
	{
		UE_LOG( LogTemp, Warning, TEXT( "%s PlayerController" ), *controlledTank->GetName() );
	}
	else
	{
		UE_LOG( LogTemp, Warning, TEXT( "PlayerController not possesing a tank" ));
	}
}


ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>( GetPawn() );
}

