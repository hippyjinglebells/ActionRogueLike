// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPickUpBase.h"
#include "SPickUp_HealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPickUp_HealthPotion : public ASPickUpBase
{
	GENERATED_BODY()

public:

	ASPickUp_HealthPotion();

protected:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComp;

	UFUNCTION()
	void Interact_Implementation(APawn* InstigatorPawn) override;
};
