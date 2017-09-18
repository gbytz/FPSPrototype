// Fill out your copyright notice in the Description page of Project Settings.

#include "DestructiblePiece.h"
#include "Components/StaticMeshComponent.h"
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
	UE_LOG(LogTemp, Warning, TEXT("Hit!"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hit"));
	Destroy();
}
