// Fill out your copyright notice in the Description page of Project Settings.
#include "ShipController.h"
#include "Ship.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"





AShipController::AShipController()
{
	bShowMouseCursor = false;
	DefaultMouseCursor = EMouseCursor::Default;
}



void AShipController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AShipController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &AShipController::OnInputStarted);

		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &AShipController::OnInputStarted);
	}
	
}

void AShipController::OnInputStarted()
{
	StopMovement();
}

void AShipController::OnMovementInput(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	APawn* ControlledPawn = GetPawn();


	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = FVector(MovementVector.X, MovementVector.Y, 0);
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}

	UE_LOG(LogTemp, Warning, TEXT("it is happening"));

}

void AShipController::OnAimInput(const FInputActionValue& Value)
{
}

