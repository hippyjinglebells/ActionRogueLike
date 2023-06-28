// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBaseProjectile.h"
#include "STeleportProjectile.generated.h"

/**
 * 
 */

class UParticleSystemComponent;


UCLASS()
class ACTIONROGUELIKE_API ASTeleportProjectile : public ASBaseProjectile
{
	GENERATED_BODY()

public:
	
	ASTeleportProjectile();

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* TeleportEffectComp;

protected:
	void ProjectileTimerElapsed();

	UFUNCTION(BlueprintCallable)
	void OnEffectFinish();
	
	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;
	FTimerHandle TimerHandle_TeleportProjectile;
	FTimerHandle TimerHandle_TeleportEffect;
};
