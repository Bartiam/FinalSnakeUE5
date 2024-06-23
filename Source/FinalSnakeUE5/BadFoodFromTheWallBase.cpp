// Fill out your copyright notice in the Description page of Project Settings.


#include "BadFoodFromTheWallBase.h"
#include "SnakeBase.h"
#include "GroundBase.h"

void ABadFoodFromTheWallBase::Interact(AActor* interactor, bool bIsHead)
{
	if (IsValid(interactor))
	{
		auto snake = Cast<ASnakeBase>(interactor);
		if (IsValid(snake))
		{
			for (int i = 0; i < 2; ++i)
				snake->SlowDownSnake(5.f, speedChangesOn);

			snake->DeleteSnakeElement();
			groundOwner->DestroyFoodInTheWorld(this);
		}
	}
}
