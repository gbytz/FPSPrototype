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

				const FVector2D BottomCenter(Canvas->ClipX * 0.5f, Canvas->ClipY);
				DrawScore(GetOwningPlayerController()->PlayerState, BottomCenter.X, BottomCenter.Y - 50, DefaultColor);
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

void AFPSPrototypeHUD::DrawScore(APlayerState* PlayerState, float X, float Y, FLinearColor TextColor)
{
	if (PlayerState != nullptr)
	{
		float MiddleSpace = 60;
		float NameWidth;	
		float NameHeight;
		float PointsWidth;
		float PointsHeight;
		GetTextSize(PlayerState->PlayerName, NameWidth, NameHeight, DefaultFont, DefaultScale);
		GetTextSize(FString::FromInt((int) PlayerState->Score), PointsWidth, PointsHeight, DefaultFont, DefaultScale);

		float NameX = X - (MiddleSpace * 0.5f) - NameWidth;
		float PointsX = X + (MiddleSpace * 0.5f);

		DrawText(PlayerState->PlayerName, TextColor, NameX, Y, DefaultFont, DefaultScale, false);
		DrawText(FString::FromInt((int) PlayerState->Score) + FString(" pts"), TextColor, PointsX, Y, DefaultFont, DefaultScale, false);
	}
}

void AFPSPrototypeHUD::DrawScoreTable(AGameState* InGameState)
{
	FVector2D CanvasCenter = FVector2D();
	Canvas->GetCenter(CanvasCenter.X, CanvasCenter.Y);
	float CanvasWidth = Canvas->SizeX;
	float CanvasHeight = Canvas->SizeY;

	float TableWidth = (CanvasWidth / 3);
	float TableHeight = (CanvasHeight / 3);
	float TableX = (CanvasCenter.X - (TableWidth * 0.5f));
	float TableY = (CanvasCenter.Y - (TableHeight * 0.5f));
	
	DrawRect(TableColor, TableX, TableY, TableWidth, TableHeight);

	float LeftPadding = 50;
	float TopPadding = 50;

	float Y = CanvasCenter.Y;
	float PlayerNameX = TableX + (TableWidth * 0.5f);
	float PlayerNameY = TableY + TopPadding;

	float PlayerNameHeight = 25;
	float PlayerNameWidth = 300;

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
		PlayerNameY = PlayerNameY + PlayerNameHeight;
	}
}