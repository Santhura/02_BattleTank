// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Public/TimerManager.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>( FName( "Collision mesh" ) );
	SetRootComponent( collisionMesh );
	collisionMesh->SetNotifyRigidBodyCollision( true );
	collisionMesh->SetVisibility( false );

	launchBlast = CreateDefaultSubobject<UParticleSystemComponent>( FName( "Launch blast" ) );
	launchBlast->AttachToComponent( RootComponent, FAttachmentTransformRules::KeepRelativeTransform );

	impactBlast = CreateDefaultSubobject<UParticleSystemComponent>( FName( "impact blast" ) );
	impactBlast->AttachToComponent( RootComponent, FAttachmentTransformRules::KeepRelativeTransform );
	impactBlast->bAutoActivate = false;

	explosionForce = CreateDefaultSubobject<URadialForceComponent>( FName( "Explosion Force" ) );
	explosionForce->AttachToComponent( RootComponent, FAttachmentTransformRules::KeepRelativeTransform );

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>( FName( "projectile Movement" ) );
	projectileMovement->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	collisionMesh->OnComponentHit.AddDynamic( this, &AProjectile::OnHit );
}

void AProjectile::LaunchProjectile( float speed )
{
	projectileMovement->SetVelocityInLocalSpace( FVector::ForwardVector * speed );
	projectileMovement->Activate();
}

void AProjectile::OnHit( UPrimitiveComponent * hitComponent, AActor * otherActor, UPrimitiveComponent * otherComponent, FVector normalImpulse, const FHitResult & hit )
{
	launchBlast->Deactivate();
	impactBlast->Activate();
	explosionForce->FireImpulse();

	SetRootComponent( impactBlast );
	collisionMesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage(
		this,
		projectileDamage,
		GetActorLocation(),
		explosionForce->Radius,// for consistancy
		UDamageType::StaticClass(),
		TArray<AActor*>() // damage all actors
	);

	FTimerHandle timer;
	GetWorld()->GetTimerManager().SetTimer( timer, this, &AProjectile::OnTimerExpire, destroyDelay, false );
}

void AProjectile::OnTimerExpire()
{
	Destroy();
}
