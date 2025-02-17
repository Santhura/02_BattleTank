// Copyright Dylan Gijsbertsen

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;
class USphereComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce( float forceMagnitude );

private:
	UFUNCTION()
	void OnHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

	void ApplyForce();
	void SetupConstraint();

	// Components
	UPROPERTY( VisibleAnywhere, Category = "Components" )
	USphereComponent * wheel = nullptr;
	UPROPERTY( VisibleAnywhere, Category = "Components" )
	USphereComponent * axle = nullptr;
	UPROPERTY( VisibleAnywhere, Category = "Components" )
	UPhysicsConstraintComponent* massWheelContraint = nullptr;
	UPROPERTY( VisibleAnywhere, Category = "Components" )
	UPhysicsConstraintComponent* axleWheelContraint = nullptr;
	

	float totalForceMagnitudeThisFrame = 0;
};
