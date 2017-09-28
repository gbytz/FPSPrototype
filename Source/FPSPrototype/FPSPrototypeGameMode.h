// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "FPSPrototypeGameMode.generated.h"

UCLASS(minimalapi)
class AFPSPrototypeGameMode : public AGameMode
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
	TArray<FColor> PossibleColors;

	/** Called when the state transitions to WaitingToStart */
	virtual void HandleMatchIsWaitingToStart() override;

	/** Called when the state transitions to InProgress */
	virtual void HandleMatchHasStarted() override;

	virtual bool ReadyToEndMatch_Implementation() override;

public:
	AFPSPrototypeGameMode();
};



