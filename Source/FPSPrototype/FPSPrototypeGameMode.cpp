// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSPrototypeGameMode.h"

#include "DestructiblePiece.h"
#include "FPSPrototypeHUD.h"
#include "FPSPrototypeCharacter.h"
#include "Public/EngineUtils.h"
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

void AFPSPrototypeGameMode::HandleMatchIsWaitingToStart()
{
	TArray<FColor> PossibleColors = { FColor::Red, FColor::Green, FColor::Blue };
	for (TActorIterator<ADestructiblePiece> Iterator(GetWorld()); Iterator; ++Iterator)
	{
		FColor PickedColor = PossibleColors[FMath::RandRange(0, PossibleColors.Num()-1)];
		Iterator->SetColor(PickedColor);
	}
}