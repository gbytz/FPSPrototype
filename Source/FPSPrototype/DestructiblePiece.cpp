// Fill out your copyright notice in the Description page of Project Settings.

#include "DestructiblePiece.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"
#include "FPSPrototypeCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"

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
	AActor* Projectile = OtherActor;
	if (Projectile != nullptr && Projectile->GetOwner() != nullptr)
	{
		Explode(Projectile->GetOwner());
	}
}

void ADestructiblePiece::SetColor(FColor InColor)
{
	UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(MeshComponent->GetMaterial(0), nullptr);
	DynamicMaterial->SetVectorParameterValue(FName("Base Color"), FLinearColor(InColor));
	MeshComponent->SetMaterial(0, DynamicMaterial);
	BaseColor = InColor;
}

void ADestructiblePiece::Explode(AActor* ProjectileOwner)
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
		CurrentPiece->CountPoits(ProjectileOwner);
		CurrentPiece->Destroy();
	}
}

void ADestructiblePiece::CountPoits(AActor* ProjectileOwner)
{
	int32 PointsToSum = NFibonacci(Points);
	AFPSPrototypeCharacter* Character = Cast<AFPSPrototypeCharacter>(ProjectileOwner);
	if (Character != nullptr)
	{
		Character->GetController()->PlayerState->Score += (float) PointsToSum;
	}
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