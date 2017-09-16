// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSPrototypeGameMode.h"
#include "FPSPrototypeHUD.h"
#include "FPSPrototypeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFPSPrototypeGameMode::AFPSPrototypeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSPrototypeHUD::StaticClass();
}
