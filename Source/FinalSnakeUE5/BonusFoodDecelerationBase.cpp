// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusFoodDecelerationBase.h"
#include "SnakeBase.h"

void ABonusFoodDecelerationBase::Interact(AActor* interactor, bool bIsHead)
{
	if (IsValid(interactor))
	{
		auto snake = Cast<ASnakeBase>(interactor);
		if (IsValid(snake))
		{
			snake->SlowDownSnake();
			Destroy();
		}
	}
}
