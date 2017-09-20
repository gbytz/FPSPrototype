// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Containers/Queue.h"
#include "DestructiblePiece.generated.h"

UCLASS()
class FPSPROTOTYPE_API ADestructiblePiece : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestructiblePiece();

	void SetColor(FColor InColor);

	void Explote();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;

	FColor BaseColor;

	UPROPERTY(EditAnywhere)
	int32 Points;

	int32 NFibonacci(int32 n);

	void CountPoits();
};
