// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickUpBase.h"

// Sets default values
ASPickUpBase::ASPickUpBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASPickUpBase::Interact_Implementation(APawn* InstigatorPawn)
{
	
}

// Called when the game starts or when spawned
void ASPickUpBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASPickUpBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

