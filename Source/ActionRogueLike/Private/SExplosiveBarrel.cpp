// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMesh;

	RadialForce = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForce->SetupAttachment(StaticMesh);

	RadialForce->Radius = 500.0f;
	RadialForce->ForceStrength = 2000.0f;
	RadialForce->ImpulseStrength = 2000.0f;
	RadialForce->bImpulseVelChange = true;
	RadialForce->bAutoActivate = false;

	
	StaticMesh->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::Explode);

	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASExplosiveBarrel::Explode(UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit)
{
	RadialForce->FireImpulse();

	StaticMesh->SetSimulatePhysics(false);
	StaticMesh->SetVisibility(false);
}

// Called when the game starts or when spawned
void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

