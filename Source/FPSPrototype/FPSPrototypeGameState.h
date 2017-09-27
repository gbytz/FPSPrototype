// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "FPSPrototypeGameState.generated.h"

/**
 *
 */
UCLASS()
class FPSPROTOTYPE_API AFPSPrototypeGameState : public AGameState
{
	GENERATED_BODY()

public:
	void SetPieceCount(uint64 InPieceCount);
	uint64 GetPieceCount();

private:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated)
	uint64 PieceCount;
};
