// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SPickUpBase.generated.h"

UCLASS(Abstract)
class ACTIONROGUELIKE_API ASPickUpBase : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPickUpBase();

	void Interact_Implementation(APawn* InstigatorPawn) override;

protected:

	UPROPERTY(VisibleAnywhere)
	UMeshComponent* MeshComp;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
