// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_Explore.h"
#include "Ship.h"
#include "ShipController.h"
#include "UObject/ConstructorHelpers.h"

AGM_Explore::AGM_Explore()
{
	// use our custom PlayerController class
	PlayerControllerClass = AShipController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Ships/BP_Ship"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/Inputs/BP_ShipController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}
