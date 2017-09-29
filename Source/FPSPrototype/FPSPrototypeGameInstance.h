// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FPSPrototypeGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROTOTYPE_API UFPSPrototypeGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:

	/** Calculates the Fibonacci number we'll need during the game
	 * @param InAmount - The amount of Fibonacci numbers we'll use
	 */
	void InitFibonaccis(const uint64 InAmount);

	/** Returns the Nth Fibonacci number
	 * @param InN - The number of the Fibonacci number we want to get
	 * @return the N-th Fibonacci number
	 */
	uint64 GetNthFibonacci(const uint64 InN) const;

private:

	TArray<uint64> FibonacciNumbers;

};
