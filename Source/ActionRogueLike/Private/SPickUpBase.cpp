// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickUpBase.h"

// Sets default values
ASPickUpBase::ASPickUpBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Powerup");
	RootComponent = SphereComp;

	RespawnTime = 10.0f;
}

void ASPickUpBase::Interact_Implementation(APawn* InstigatorPawn)
{
	//logic in derived classes
}

void ASPickUpBase::ShowPowerup()
{
	SetPowerupState(true);
}

void ASPickUpBase::HideAndCooldownPowerup()
{
	SetPowerupState(false);

	GetWorldTimerManager().SetTimer(TimerHandle_RespawnTimer, this, &ASPickUpBase::ShowPowerup, RespawnTime);
}

void ASPickUpBase::SetPowerupState(bool bNewIsActive)
{
	SetActorEnableCollision(bNewIsActive);

	//Set visibility on root and all children
	RootComponent->SetVisibility(bNewIsActive, true);
}





