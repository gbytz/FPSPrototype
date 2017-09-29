// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSPrototypeHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "Classes/Engine/World.h"

AFPSPrototypeHUD::AFPSPrototypeHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshairTexObj.Object;

	static ConstructorHelpers::FObjectFinder<UFont> FontObj(TEXT("/Game/FirstPerson/Fonts/Paintball_Beta_4a_Font.Paintball_Beta_4a_Font"));
	if (FontObj.Succeeded())
	{
		DefaultFont = FontObj.Object;
	}
}

void AFPSPrototypeHUD::DrawHUD()
{
	Super::DrawHUD();
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		AGameState* CurrentGameState = GetWorld()->GetGameState<AGameState>();
		if (CurrentGameState != nullptr)
		{
			if (CurrentGameState->IsMatchInProgress()) {
				DrawCrosshair();

				const FVector2D TopCenter(Canvas->ClipX * 0.5f, 0);
				DrawScore(GetOwningPlayerController()->PlayerState, TopCenter.X, TopCenter.Y + 50, DefaultColor);
			}
			else if(CurrentGameState->HasMatchEnded())
			{
				DrawScoreTable(CurrentGameState);
			}
		}
	}
}

void AFPSPrototypeHUD::DrawCrosshair()
{
	// Draw very simple crosshair

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition((Center.X), (Center.Y + 20.0f));

	// draw the crosshair
	FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}

void AFPSPrototypeHUD::DrawScore(APlayerState* InPlayerState, const float InX, const float InY, const FLinearColor InTextColor)
{
	if (InPlayerState != nullptr)
	{
		// Magic number to set the space between the player name and the score
		const float MiddleSpace = 80.0f;

		// Calculates player name text size
		float NameWidth;	
		float NameHeight;
		GetTextSize(InPlayerState->PlayerName, NameWidth, NameHeight, DefaultFont, DefaultScale);

		const float NameX = InX - (MiddleSpace * 0.5f) - NameWidth;
		DrawText(InPlayerState->PlayerName, InTextColor, NameX, InY, DefaultFont, DefaultScale, false);

		// Calculates the score text size
		const FString ScoreText = FString::FromInt((int)InPlayerState->Score) + FString(" pts");
		float ScoreWidth;
		float ScoreHeight;
		GetTextSize(ScoreText, ScoreWidth, ScoreHeight, DefaultFont, DefaultScale);

		const float ScoreX = InX + (MiddleSpace * 0.5f);
		DrawText(ScoreText, InTextColor, ScoreX, InY, DefaultFont, DefaultScale, false);
	}
}

void AFPSPrototypeHUD::DrawScoreTable(AGameState* InGameState)
{
	FVector2D CanvasCenter = FVector2D();
	Canvas->GetCenter(CanvasCenter.X, CanvasCenter.Y);
	const float CanvasWidth = Canvas->SizeX;
	const float CanvasHeight = Canvas->SizeY;

	float TextWidth;
	float TextHeight;
	GetTextSize(TEXT("A"), TextWidth, TextHeight, DefaultFont, DefaultScale);

	// Calculates the table height based on content I'll have
	const float VerticalSpacing = 3.5f;
	const float ContentHeigh = InGameState->PlayerArray.Num() * (TextHeight + VerticalSpacing) + VerticalSpacing;
	const float DefaultTableHeigh = (CanvasHeight / 3.0f);
	const float TableHeight = ContentHeigh > DefaultTableHeigh ? ContentHeigh : DefaultTableHeigh;

	// Calculates the table width
	const float TableWidth = (CanvasWidth / 3.0f);
	const float TableX = (CanvasCenter.X - (TableWidth * 0.5f));
	const float TableY = (CanvasCenter.Y - (TableHeight * 0.5f));

	DrawRect(TableColor, TableX, TableY, TableWidth, TableHeight);

	// Draw the list of players
	const float PlayerNameX = TableX + (TableWidth * 0.5f);
	float PlayerNameY = TableY + (TableHeight * 0.5f) - (ContentHeigh * 0.5) + VerticalSpacing;
	for (APlayerState* PlayerState : InGameState->PlayerArray)
	{
		if (PlayerState == GetOwningPlayerController()->PlayerState)
		{
			DrawScore(PlayerState, PlayerNameX, PlayerNameY, PlayerColor);
		}
		else 
		{
			DrawScore(PlayerState, PlayerNameX, PlayerNameY, DefaultColor);
		}
		PlayerNameY = PlayerNameY + TextHeight + VerticalSpacing;
	}

	// Draw the header of the table;
	const FString HeaderText = FString(TEXT("Leaderboard"));
	float HeaderTextWidth;
	float HeaderTextHeight;
	const float HeaderTextScale = DefaultScale * 1.50f;
	GetTextSize(HeaderText, HeaderTextWidth, HeaderTextHeight, DefaultFont, HeaderTextScale);

	const float HeaderBackgroundWidth = TableWidth * 1.05f;
	const float HeaderBackgroundX = (CanvasCenter.X - (HeaderBackgroundWidth * 0.5f));;
	const float HeaderBackgroundHeight = HeaderTextHeight * 1.5f;
	const float HeaderBackgroundY = TableY - HeaderBackgroundHeight;
	DrawRect(HeaderBackgroundColor, HeaderBackgroundX, HeaderBackgroundY, HeaderBackgroundWidth, HeaderBackgroundHeight);

	const float HeaderTextX = HeaderBackgroundX + ((HeaderBackgroundWidth - HeaderTextWidth) * 0.5f);
	const float HeaderTextY = HeaderBackgroundY - ((HeaderTextHeight - HeaderBackgroundHeight) * 0.5f);
	DrawText(HeaderText, HeaderTextColor, HeaderTextX, HeaderTextY, DefaultFont, HeaderTextScale);
}