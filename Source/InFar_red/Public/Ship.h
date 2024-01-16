// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Ship.generated.h"

UCLASS()
class INFAR_RED_API AShip : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShip();


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = CameraSettings)
		class UArrowComponent* CameraOriginLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = CameraSettings)
		class UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = CameraSettings)
		class USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, Category = CameraSettings)
		float DefaultCameraPitch = -70;

	UPROPERTY(EditAnywhere, Category = CameraSettings)
		float DefaultCameraYaw = -5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Lag, meta = (editcondition = "bEnableCameraLag", ClampMin = "0.0", ClampMax = "1000.0", UIMin = "0.0", UIMax = "1000.0"))
		float CameraLagSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Lag, AdvancedDisplay, meta = (editcondition = "bUseCameraLagSubstepping", ClampMin = "0.005", ClampMax = "0.5", UIMin = "0.005", UIMax = "0.5"))
		float CameraLagMaxTimeStep;

	/** Max distance the camera target may lag behind the current location. If set to zero, no max distance is enforced. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lag, meta = (editcondition = "bEnableCameraLag", ClampMin = "0.0", UIMin = "0.0"))
		float CameraLagMaxDistance;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void SetupCameraComponent();

};
