// Fill out your copyright notice in the Description page of Project Settings.

#include "DestructiblePiece.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"

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
	BoxComponent->SetBoxExtent(FVector(55.0f));
	BoxComponent->SetHiddenInGame(false);
	BoxComponent->SetupAttachment(RootComponent);

	Points = 0;
}

// Called when the game starts or when spawned
void ADestructiblePiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestructiblePiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
							  
void ADestructiblePiece::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("Hit on %s!"), *GetName());
	Explote();
}

void ADestructiblePiece::SetColor(FColor InColor)
{
	UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(MeshComponent->GetMaterial(0), nullptr);
	DynamicMaterial->SetVectorParameterValue(FName("Base Color"), FLinearColor(InColor));
	MeshComponent->SetMaterial(0, DynamicMaterial);
	BaseColor = InColor;
}

void ADestructiblePiece::Explote()
{
	TSet<ADestructiblePiece*> DiscoveredPieces;
	DiscoveredPieces.Add(this);

	TQueue<ADestructiblePiece*> PiecesToDestroy;
	PiecesToDestroy.Enqueue(this);

	this->Points = 1;

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
				OtherPiece->Points = CurrentPiece->Points + 1;
			}
		}
		CurrentPiece->CountPoits();
		CurrentPiece->Destroy();
	}
}

void ADestructiblePiece::CountPoits()
{
	UE_LOG(LogTemp, Warning, TEXT("%s sums %d Points"), *GetName(), NFibonacci(Points));
}

int32 ADestructiblePiece::NFibonacci(int32 n)
{
	int32 PreviousFib = 0;
	int32 CurrentFib = 1;
	for (int32 step = 0; step < n; ++step)
	{
		CurrentFib = CurrentFib + PreviousFib;
		PreviousFib = CurrentFib - PreviousFib;
	}
	return PreviousFib;
}