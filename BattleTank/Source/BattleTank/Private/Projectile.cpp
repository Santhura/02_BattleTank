// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>( FName( "Collision mesh" ) );
	SetRootComponent( collisionMesh );
	collisionMesh->SetNotifyRigidBodyCollision( true );
	collisionMesh->SetVisibility( false );

	launchBlast = CreateDefaultSubobject<UParticleSystemComponent>( FName( "Launch blast" ) );
	launchBlast->AttachTo( RootComponent );

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>( FName( "projectile Movement" ) );
	projectileMovement->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile( float speed )
{
	projectileMovement->SetVelocityInLocalSpace( FVector::ForwardVector * speed );
	projectileMovement->Activate();
}

