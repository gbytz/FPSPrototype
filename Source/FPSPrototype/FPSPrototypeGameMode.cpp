// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSPrototypeGameMode.h"

#include "DestructiblePiece.h"
#include "FPSPrototypeHUD.h"
#include "FPSPrototypeGameState.h"
#include "FPSPrototypeGameInstance.h"
#include "Public/EngineUtils.h"
#include "UObject/ConstructorHelpers.h"

AFPSPrototypeGameMode::AFPSPrototypeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// Use my custom HUD class
	HUDClass = AFPSPrototypeHUD::StaticClass();

	// Use my custom GameState class
	GameStateClass = AFPSPrototypeGameState::StaticClass();

	// Set the default possible colors.
	PossibleColors = { FColor::Red, FColor::Green, FColor::Blue };
}

void AFPSPrototypeGameMode::HandleMatchIsWaitingToStart()
{
	Super::HandleMatchIsWaitingToStart();
}

void AFPSPrototypeGameMode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();

	AFPSPrototypeGameState* CustomGameState = GetGameState<AFPSPrototypeGameState>();
	CustomGameState->SetPieceCount(0);
	for (TActorIterator<ADestructiblePiece> PieceIterator(GetWorld()); PieceIterator; ++PieceIterator)
	{
		ADestructiblePiece* Piece = *PieceIterator;
		FColor PickedColor = GetPossibleColor();
		Piece->SetColor(PickedColor);
		Piece->OnRep_BaseColor(); // Change the piece material color in the server.
		CustomGameState->SetPieceCount(CustomGameState->GetPieceCount() + 1);
	}

	UFPSPrototypeGameInstance* ThisGameInstance = Cast<UFPSPrototypeGameInstance>(GetGameInstance());
	ThisGameInstance->InitFibonaccis(CustomGameState->GetPieceCount());
}

void AFPSPrototypeGameMode::HandleMatchHasEnded()
{
	Super::HandleMatchHasEnded();
}

bool AFPSPrototypeGameMode::ReadyToEndMatch_Implementation()
{
	AFPSPrototypeGameState* CustomGameState = GetGameState<AFPSPrototypeGameState>();
	const bool bReadyToEndMatch = (CustomGameState->GetPieceCount() == 0);
	return bReadyToEndMatch;
}

FColor AFPSPrototypeGameMode::GetPossibleColor() const
{
	return PossibleColors[FMath::RandRange(0, PossibleColors.Num() - 1)];
}
