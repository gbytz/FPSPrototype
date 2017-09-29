// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "FPSPrototypeGameState.generated.h"

UCLASS()
class FPSPROTOTYPE_API AFPSPrototypeGameState : public AGameState
{
	GENERATED_BODY()

public:

	/**
	 * Sets the internal piece counter value
	 * @param InPieceCount - New value of the piece counter
	 */
	void SetPieceCount(const uint64 InPieceCount);

	/** @return the value of the piece counter */
	uint64 GetPieceCount() const;

protected:

	/** Called when the map transitions to WaitingPostMatch */
	virtual void HandleMatchHasEnded() override;

private:

	/** Returns properties that are replicated for the lifetime of the actor channel */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Takes acount of the number of remaining pieces in the current game */
	UPROPERTY(Replicated)
	uint64 PieceCount;
};
