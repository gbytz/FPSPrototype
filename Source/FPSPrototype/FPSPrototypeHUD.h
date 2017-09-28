// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameFramework/GameState.h"
#include "FPSPrototypeHUD.generated.h"

UCLASS()
class AFPSPrototypeHUD : public AHUD
{
	GENERATED_BODY()

public:
	AFPSPrototypeHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

	class UFont* DefaultFont;

	float DefaultScale = 2.0f;

	FLinearColor DefaultColor = FLinearColor::White;
	FLinearColor PlayerColor = FLinearColor::Green;
	FLinearColor TableColor = FLinearColor(0.5, 0.5, 0.5, 0.5);

	void DrawCrosshair();
	void DrawScore(APlayerState* PlayerState, float X, float Y, FLinearColor TextColor);
	void DrawScoreTable(AGameState* InGameState);
};

