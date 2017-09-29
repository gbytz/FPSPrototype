// Fill out your copyright notice in the Description page of Project Settings.

#include "DestructiblePiece.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"
#include "FPSPrototypeCharacter.h"
#include "FPSPrototypeGameState.h"
#include "FPSPrototypeGameInstance.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ADestructiblePiece::ADestructiblePiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualComponent"));
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->OnComponentHit.AddDynamic(this, &ADestructiblePiece::OnHit);
	RootComponent = MeshComponent;

	// This use a hardcoded path for now.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> VisualComponentAsset(TEXT("/Game/Geometry/Meshes/1M_Cube.1M_Cube"));
	if (VisualComponentAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(VisualComponentAsset.Object);
	}

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComponent"));
	BoxComponent->SetBoxExtent(FVector(51.0f));
	BoxComponent->SetupAttachment(RootComponent);

	DestructionLevel = 0;

	SetReplicates(true);
	SetReplicateMovement(true);
}
							  
void ADestructiblePiece::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Role == ROLE_Authority)
	{
		AActor* ProjectileOwner = OtherActor->GetOwner();
		if (ProjectileOwner != nullptr)
		{
			Explode(ProjectileOwner);
		}
	}
}

void ADestructiblePiece::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADestructiblePiece, BaseColor);
}

void ADestructiblePiece::OnRep_BaseColor()
{
	UMaterialInstanceDynamic* DynamicMaterial = MeshComponent->CreateAndSetMaterialInstanceDynamic(0);
	DynamicMaterial->SetVectorParameterValue(FName("Base Color"), FLinearColor(BaseColor));
}

void ADestructiblePiece::SetColor(FColor InColor)
{
	BaseColor = InColor;
}

void ADestructiblePiece::Explode(AActor* InProjectileOwner)
{
	TSet<ADestructiblePiece*> DiscoveredPieces;
	DiscoveredPieces.Add(this);

	TQueue<ADestructiblePiece*> PiecesToDestroy;
	PiecesToDestroy.Enqueue(this);

	this->DestructionLevel = 1;

	ADestructiblePiece* CurrentPiece;
	TArray<AActor*> OverlappingPieces;

	while ( !PiecesToDestroy.IsEmpty() )
	{		
		PiecesToDestroy.Dequeue(CurrentPiece);
		CurrentPiece->GetOverlappingActors(OverlappingPieces, ADestructiblePiece::StaticClass());
		for (AActor* OtherActor : OverlappingPieces)
		{
			ADestructiblePiece* OtherPiece = Cast<ADestructiblePiece>(OtherActor);
			if (OtherPiece->BaseColor == BaseColor && !DiscoveredPieces.Contains(OtherPiece))
			{
				DiscoveredPieces.Add(OtherPiece);
				PiecesToDestroy.Enqueue(OtherPiece);
				OtherPiece->DestructionLevel = CurrentPiece->DestructionLevel + 1;
			}
		}
		CurrentPiece->CountPoits(InProjectileOwner);
		CurrentPiece->Destroy();
		
		UWorld* World = GetWorld();
		if(World != nullptr)
		{
			AFPSPrototypeGameState* CustomGameState = World->GetGameState<AFPSPrototypeGameState>();
			CustomGameState->SetPieceCount(CustomGameState->GetPieceCount() - 1);
		}
	}
}

void ADestructiblePiece::CountPoits(AActor* InProjectileOwner)
{
	APlayerController* PlayerController = Cast<APlayerController>(InProjectileOwner);
	if (PlayerController != nullptr)
	{
		UFPSPrototypeGameInstance* ThisGameInstance = Cast<UFPSPrototypeGameInstance>(GetGameInstance());
		PlayerController->PlayerState->Score += (float)ThisGameInstance->GetNthFibonacci(DestructionLevel);
	}
}
