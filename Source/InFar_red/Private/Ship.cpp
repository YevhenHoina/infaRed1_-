// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AShip::AShip()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetupCameraComponent();
}

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AShip::SetupCameraComponent()
{
	CameraOriginLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("CameraOriginLocation"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraOriginLocation->SetupAttachment(GetMesh());
	CameraComp->SetupAttachment(GetMesh());

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));

	//Attach the Spring Arm to the Character's Skeletal Mesh Component
	SpringArmComp->SetupAttachment(GetMesh());

	//Attach the Camera to the SpringArmComponent
	CameraComp->AttachToComponent(SpringArmComp, FAttachmentTransformRules::KeepRelativeTransform);

	SpringArmComp->bUsePawnControlRotation = false;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->SetWorldRotation(FRotator(CameraPitch, CameraYaw, 0));
}
