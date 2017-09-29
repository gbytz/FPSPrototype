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

	/**
	 * Sets the color of the piece
	 * @param InColor - The color the piece will be
	 */
	void SetColor(FColor InColor);

	/**
	 * Destroys a piece and every other adyacent piece of the same color in a BFS traversal way 
	 * @param InProjectileOwner - Pointer to the actor who shot the projectile
	 */
	void Explode(AActor* InProjectileOwner);

	/**
	* Increase the score of the player received by parameter
	* @param InProjectileOwner - Pointer to the actor who shot the projectile
	*/
	void CountPoits(AActor* InProjectileOwner);

	/** Called when the BaseColor property is replicated */
	UFUNCTION()
	void OnRep_BaseColor();

	/** Called when the piece is hit by other actor */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

private:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** The color of the piece */
	UPROPERTY(ReplicatedUsing = OnRep_BaseColor)
	FColor BaseColor;

	/** Visual mesh component of the piece */
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

	/** Box component used to generate overlapping events */
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;

	/** Takes acount of the "distance" from the initial hit in a sequence of pieces destruction */
	UPROPERTY(EditAnywhere)
	int64 DestructionLevel;

};
