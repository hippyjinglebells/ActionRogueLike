// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"
#include "SGameplayInterface.h"
#include "Camera/CameraComponent.h"

void USInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();


	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	UCameraComponent* CameraComp = MyOwner->GetComponentByClass<UCameraComponent>();
	TArray<FHitResult> Targets;
	FVector Start = CameraComp->GetComponentLocation();
	FVector End = Start + (CameraComp->GetComponentRotation().Vector()*10000);

	float Radius = 30.0f;
	
	FCollisionShape Shape;
	Shape.SetSphere(Radius);
	
	GetWorld()->SweepMultiByObjectType(Targets, Start, End, FQuat::Identity, ObjectQueryParams, Shape);
	//DrawDebugLine(GetWorld(), Start, End, FColor::Cyan, false, 2.0f, 0, 2.0f);
	
	for (FHitResult Target : Targets)
	{
		
			FVector TargetLocation = Target.ImpactPoint;
			FRotationMatrix NewRotation = FRotationMatrix(EyeRotation);
			NewRotation = NewRotation.MakeFromX(TargetLocation - EyeLocation).Rotator();

			End = EyeLocation + (NewRotation.Rotator().Vector() * 1000);

	}
	
	//FHitResult Hit;
	//bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);

	TArray<FHitResult> Hits;
	
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<USGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);
			
				ISGameplayInterface::Execute_Interact(HitActor, MyPawn);
				break;
			}
		}

		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, LineColor, false, 2.0f);

	}
		
	DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);
}

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

