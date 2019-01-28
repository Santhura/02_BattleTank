// Copyright Dylan Gijsbertsen

#include "SprungWheel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	massWheelContraint = CreateDefaultSubobject<UPhysicsConstraintComponent>( FName( "Physics Contraint" ) );
	SetRootComponent( massWheelContraint );

	axle = CreateDefaultSubobject<USphereComponent>( FName( "Axle" ) );
	axle->SetupAttachment( massWheelContraint );

	wheel = CreateDefaultSubobject<USphereComponent>( FName( "Wheel" ) );
	wheel->SetupAttachment( axle );

	axleWheelContraint = CreateDefaultSubobject<UPhysicsConstraintComponent>( FName( "AxleWheelContraint" ) );
	axleWheelContraint->SetupAttachment( axle );

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	wheel->SetNotifyRigidBodyCollision( true );
	wheel->OnComponentHit.AddDynamic( this, &ASprungWheel::OnHit );

	SetupConstraint();
}

void ASprungWheel::SetupConstraint()
{
	if( !GetAttachParentActor() ) return;

	UPrimitiveComponent* bodyRoot = Cast<UPrimitiveComponent>( GetAttachParentActor()->GetRootComponent() );
	if( !bodyRoot ) return;
	massWheelContraint->SetConstrainedComponents( bodyRoot, NAME_None, axle, NAME_None );
	axleWheelContraint->SetConstrainedComponents( axle, NAME_None, wheel, NAME_None );

}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if( GetWorld()->TickGroup == TG_PostPhysics )
	{
		totalForceMagnitudeThisFrame = 0;
	}
}

void ASprungWheel::AddDrivingForce( float forceMagnitude )
{
	totalForceMagnitudeThisFrame += forceMagnitude;
}

void ASprungWheel::ApplyForce()
{
	wheel->AddForce( axle->GetForwardVector() * totalForceMagnitudeThisFrame );
}

void ASprungWheel::OnHit( UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit )
{
	ApplyForce();
}

