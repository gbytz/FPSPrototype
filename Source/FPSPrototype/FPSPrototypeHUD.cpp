// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSPrototypeHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"

AFPSPrototypeHUD::AFPSPrototypeHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshairTexObj.Object;
}

void AFPSPrototypeHUD::DrawHUD()
{
	Super::DrawHUD();
	DrawCrosshair();
	DrawScore();
}

FString AFPSPrototypeHUD::GetScoreString(float Score)
{
	const FString ScoreText = FString::Printf(TEXT("Score: %i"), (int) Score);
	return ScoreText;
}

void AFPSPrototypeHUD::DrawCrosshair()
{
	// Draw very simple crosshair

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition((Center.X),
		(Center.Y + 20.0f));

	// draw the crosshair
	FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}

void AFPSPrototypeHUD::DrawScore()
{
	// Its seems PlayerState is null at the beggining of the game so I check its a valid pointer before trying to get the score.
	if (PlayerOwner != nullptr && PlayerOwner->PlayerState != nullptr)
	{
		const FVector2D BottomRight(Canvas->ClipX, Canvas->ClipY);
		const FVector2D ScoreDrawPosition((BottomRight.X - 150), BottomRight.Y - 50);
		DrawText(GetScoreString(PlayerOwner->PlayerState->Score), FLinearColor::Red, ScoreDrawPosition.X, ScoreDrawPosition.Y, nullptr, 2.0f, false);
	}
}