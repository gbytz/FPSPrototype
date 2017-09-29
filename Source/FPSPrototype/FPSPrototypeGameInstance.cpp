// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSPrototypeGameInstance.h"




void UFPSPrototypeGameInstance::InitFibonaccis(const uint64 InAmount)
{
	FibonacciNumbers = TArray<uint64>();
	FibonacciNumbers.Add(0);
	FibonacciNumbers.Add(1);
	for (uint64 Index = 2; Index <= InAmount; ++Index)
	{
		FibonacciNumbers.Add(FibonacciNumbers[Index - 1] + FibonacciNumbers[Index - 2]);
	}
}

uint64 UFPSPrototypeGameInstance::GetNthFibonacci(const uint64 InN) const
{
	return FibonacciNumbers[InN];
}
