// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "SInteractionComponent.h"
#include "Math/RotationMatrix.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//Instantiate and attach SpringArm and Camera
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComponent = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	bUseControllerRotationYaw = false;
	
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("UltimateAttack", IE_Pressed, this, &ASCharacter::UltimateAttack);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("Teleport", IE_Pressed, this, &ASCharacter::Teleport);

}

void ASCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0F;
	
	AddMovementInput(ControlRot.Vector(), Value);
}

void ASCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0F;
	
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	
	AddMovementInput(RightVector, Value);
}

void ASCharacter::PrimaryInteract()
{
	if (InteractionComponent)
	{
		InteractionComponent->PrimaryInteract();
	}
}


//Start code dump for projectiles
void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);
	
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, 0.2f);
}

void ASCharacter::PrimaryAttack_TimeElapsed()
{
	Attack_TimeElapsed(PrimaryProjectileClass);
}

void ASCharacter::UltimateAttack()
{
	PlayAnimMontage(AttackAnim);
	
	GetWorldTimerManager().SetTimer(TimerHandle_UltimateAttack, this, &ASCharacter::UltimateAttack_TimeElapsed, 0.2f);
}

void ASCharacter::UltimateAttack_TimeElapsed()
{
	Attack_TimeElapsed(UltimateProjectileClass);	
}

void ASCharacter::Teleport()
{
	PlayAnimMontage(AttackAnim);
	
	GetWorldTimerManager().SetTimer(TimerHandle_Teleport, this, &ASCharacter::Teleport_TimeElapsed, 0.2f);
}

void ASCharacter::Teleport_TimeElapsed()
{
	Attack_TimeElapsed(TeleportProjectileClass);
}


void ASCharacter::Attack_TimeElapsed(TSubclassOf<AActor> ProjectileClass)
{
	
	if(ensure(ProjectileClass))
	{
		//Initialize Parameters for spawning a projectile
		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		//LineCast to determine if cross-hair is on a Target
		FHitResult Target;
		FVector Start = CameraComp->GetComponentLocation();
		FVector End = Start + (CameraComp->GetComponentRotation().Vector()*10000);
		bool bTarget = GetWorld()->LineTraceSingleByObjectType(Target, Start, End, ObjectQueryParams);

		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
		FTransform SpawnTM;

		

		//Adjust spawn rotation to point at target
		if (bTarget)
		{
			UE_LOG(LogTemp, Log, TEXT("Target %s"), *Target.ImpactPoint.ToString())
			
			FVector TargetLocation = Target.ImpactPoint;
			FRotationMatrix NewRotation = FRotationMatrix(GetControlRotation());
			NewRotation = NewRotation.MakeFromX(TargetLocation - HandLocation).Rotator();
			
			SpawnTM = FTransform(NewRotation.Rotator(), HandLocation);
			GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("No Target"))
			
			SpawnTM = FTransform(GetControlRotation(),HandLocation);
			GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
		}
		
	}

}

