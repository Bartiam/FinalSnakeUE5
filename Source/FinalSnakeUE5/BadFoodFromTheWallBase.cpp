// Fill out your copyright notice in the Description page of Project Settings.


#include "BadFoodFromTheWallBase.h"
#include "SnakeBase.h"

void ABadFoodFromTheWallBase::Interact(AActor* interactor, bool bIsHead)
{
	if (IsValid(interactor))
	{
		auto snake = Cast<ASnakeBase>(interactor);
		if (IsValid(snake))
		{
			snake->DeleteSnakeElement();
			Destroy();
		}
	}
}
