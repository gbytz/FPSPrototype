// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSPrototypeGameState.h"
#include "Net/UnrealNetwork.h"

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