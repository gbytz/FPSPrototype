// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "FPSPrototypeGameMode.generated.h"

UCLASS(minimalapi)
class AFPSPrototypeGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AFPSPrototypeGameMode();

protected:

	UPROPERTY(EditAnywhere)
	TArray<FColor> PossibleColors;

	/** Called when the state transitions to WaitingToStart */
	virtual void HandleMatchIsWaitingToStart() override;

	/** Called when the state transitions to InProgress */
	virtual void HandleMatchHasStarted() override;

	/** Called when the map transitions to WaitingPostMatch */
	virtual void HandleMatchHasEnded() override;

	/** @return true if ready to End Match. */
	virtual bool ReadyToEndMatch_Implementation() override;

	/** @return a color picked from the PossibleColors array */
	virtual FColor GetPossibleColor() const;
};
