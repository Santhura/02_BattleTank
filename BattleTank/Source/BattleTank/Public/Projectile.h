// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class URadialForceComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	void LaunchProjectile( float speed );

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent * collisionMesh = nullptr;

	UPROPERTY( EditDefaultsOnly, Category = "Components" )
	UParticleSystemComponent * launchBlast = nullptr;

	UPROPERTY( EditDefaultsOnly, Category = "Components" )
	UParticleSystemComponent * impactBlast = nullptr;

	UPROPERTY( EditDefaultsOnly, Category = "Components" )
	URadialForceComponent * explosionForce = nullptr;

	UProjectileMovementComponent * projectileMovement = nullptr;


	UFUNCTION()
		void OnHit( UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult& hit );

};
