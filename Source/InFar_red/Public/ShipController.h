// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "ShipController.generated.h"
//#include "D:/EpicGames/Epic Games/Games/UE_5.3/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputLibrary.h"

/**
 * 
 */
UCLASS()
class INFAR_RED_API AShipController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AShipController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		float ShortPressThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* AimAction;

protected:

	virtual void SetupInputComponent() override;
	// To add mapping context
	virtual void BeginPlay();

	void OnInputStarted();
	void OnMovementInput(const FInputActionValue& Value);
	void OnAimInput(const FInputActionValue& Value);
	/** Input handlers for SetDestination action. */
};
