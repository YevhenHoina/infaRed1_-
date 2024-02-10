// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Math/Rotator.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <math.h>
#include "Math/UnrealMathUtility.h"
// Sets default values
AShip::AShip()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetupCameraComponent();
	SetupShip();

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->GravityScale = 0.0f;

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called every frame
void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//rotate ship
	const FRotator CurrentRotation = GetActorRotation();
	const FRotator TargetRotation(0, currentRotationGoal, 0);  
	const FRotator NewRotation = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaTime, RotationSpeed);
	SetActorRotation(NewRotation);

}

// Called to bind functionality to input
void AShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	AShip::bSimGravityDisabled = 1;

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShip::Move);
		//EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Triggered, this, &AShip::Aim);
	}

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void AShip::SetupShip()
{
	Direction = CreateDefaultSubobject<UArrowComponent>(TEXT("Direction"));
	Direction->SetupAttachment(GetMesh());
	Direction->bTreatAsASprite = true;


}

void AShip::SetupCameraComponent()
{
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	
	CameraComp->SetupAttachment(GetMesh());

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));

	//Attach the Spring Arm to the Character's Skeletal Mesh Component
	SpringArmComp->SetupAttachment(GetMesh());

	//Attach the Camera to the SpringArmComponent
	CameraComp->AttachToComponent(SpringArmComp, FAttachmentTransformRules::KeepRelativeTransform);

	SpringArmComp->bUsePawnControlRotation = false;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->SetWorldRotation(FRotator(DefaultCameraPitch, DefaultCameraYaw, 0));
}




void AShip::Move(const FInputActionValue& Value)
{
	const FVector2D movement = Value.Get<FVector2D>();
	
	currentRotationGoal = 57.3 * atan(movement.X / movement.Y);
	currentRotationGoal += movement.Y < 0 ? 180 : 0;
	if ((Controller != nullptr) && (movement != FVector2D(0.0f, 0.0f)))
	{
		// Add movement in that direction
		AddMovementInput(FVector(1, 0, 0), movement.Y);
		AddMovementInput(FVector(0, 1, 0), movement.X);
	}

}

void AShip::Aim(const FInputActionValue& AxisValue)
{
	//SetActorRotation(FRotator(0, 57.3 * atan(movement.X / movement.Y, 0));
}


