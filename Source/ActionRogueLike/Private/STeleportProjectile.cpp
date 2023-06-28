// Fill out your copyright notice in the Description page of Project Settings.


#include "STeleportProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

ASTeleportProjectile::ASTeleportProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	TeleportEffectComp = CreateDefaultSubobject<UParticleSystemComponent>("TeleportEffectComp");
	TeleportEffectComp->SetupAttachment(RootComponent);
}

void ASTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(TimerHandle_TeleportProjectile, this, &ASTeleportProjectile::ProjectileTimerElapsed, 0.2);
}

void ASTeleportProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASTeleportProjectile::ProjectileTimerElapsed()
{
	UE_LOG(LogTemp, Log, TEXT("ProjectileTimerElapsed Function Triggered"));
	MovementComp->Velocity = FVector::ZeroVector;

	TeleportEffectComp->Activate();

	GetWorldTimerManager().SetTimer(TimerHandle_TeleportEffect, this, &ASTeleportProjectile::OnEffectFinish, 0.2);
}

void ASTeleportProjectile::OnEffectFinish()
{
	UE_LOG(LogTemp, Log, TEXT("OnEffectFinish Function Triggered"));
	APawn* MyInstigator = GetInstigator();
	MyInstigator->SetActorLocation(SphereComp->GetComponentLocation());

	this->Destroy();
}

