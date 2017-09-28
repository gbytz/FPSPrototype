// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSPrototypeGameState.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Algo/Sort.h"

void AFPSPrototypeGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFPSPrototypeGameState, PieceCount);
}

void AFPSPrototypeGameState::SetPieceCount(uint64 InPieceCount)
{
	// Only the server can set the piece count
	if (Role == ROLE_Authority)
	{
		PieceCount = InPieceCount;
	}
}

uint64 AFPSPrototypeGameState::GetPieceCount()
{
	return PieceCount;
}

void AFPSPrototypeGameState::HandleMatchHasEnded()
{
	Super::HandleMatchHasEnded();

	// Sort the players array by score. Done here so its only sorted once.
	Algo::Sort(PlayerArray,
		[](APlayerState* A, APlayerState* B)
		{
			return A->Score > B->Score;
		}
	);
}