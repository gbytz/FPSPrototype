// Fill out your copyright notice in the Description page of Project Settings.

#include "DestructiblePiece.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ADestructiblePiece::ADestructiblePiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set the BoxComponent for collisions
	UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	RootComponent = BoxComponent;
	BoxComponent->InitBoxExtent(FVector(10.0f));
	BoxComponent->SetSimulatePhysics(true);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	// BoxComponent->SetCollisionProfileName(TEXT("DestructiblePiece"));

	UStaticMeshComponent* BoxVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualBox"));
	BoxVisual->SetupAttachment(RootComponent);
	
	// This use a hardcoded path for now.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxVisualAsset(TEXT("/Game/Geometry/Meshes/1M_Cube.1M_Cube"));
	if (BoxVisualAsset.Succeeded())
	{
		BoxVisual->SetStaticMesh(BoxVisualAsset.Object);
		BoxVisual->SetRelativeLocation(FVector::ZeroVector);
	}
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

