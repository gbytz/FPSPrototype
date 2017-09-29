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

	/** Draws a crosshair in the center of the screen */
	void DrawCrosshair();

	/**
	 * Draws the name of the player and her score
	 * @param InPlayerState - Pointer to the player whose name and score will be draw
	 * @param InX - Position where the score will be draw relative to the left of the screen
	 * @param InY - Position where the score will be draw relative to the top of the screen
	 * @param InTextColor - The color which will be used to draw the score
	 */
	void DrawScore(APlayerState* InPlayerState, const float InX, const float InY, const FLinearColor InTextColor);

	/**
	 * Draws a table with the name and score of all the players in the game
	 * @param InGameState - Pointer to the game state instance.
	 */
	void DrawScoreTable(AGameState* InGameState);

	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

	/** Default hud font */
	class UFont* DefaultFont;

	/** Default hud scale */
	float DefaultScale = 1.0f;

	/** Color used to draw evey player in the final leaderboard table except from the owner of this hud */
	const FLinearColor DefaultColor = FLinearColor::White;

	/** Color used to highlight the player in the final leaderboard table */
	const FLinearColor PlayerColor = FLinearColor::Green;

	/** Color of the final leaderboard table */
	const FLinearColor TableColor = FLinearColor(0.5, 0.5, 0.5, 0.5);

	/** Color of the table header text */
	const FLinearColor HeaderTextColor = FLinearColor(FColor::Orange);

	/** Color of the table header background */
	const FLinearColor HeaderBackgroundColor = FLinearColor(0, 0, 0, 0.75);

};
