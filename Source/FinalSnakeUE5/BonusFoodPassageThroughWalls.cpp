// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusFoodPassageThroughWalls.h"
#include "SnakeBase.h"
#include "GroundBase.h"

void ABonusFoodPassageThroughWalls::Interact(AActor* interactor, bool bIsHead)
{
	if (IsValid(interactor))
	{
		auto snake = Cast<ASnakeBase>(interactor);
		if (IsValid(snake))
		{
			groundOwner->ToggleCollisionWall();
			groundOwner->DestroyFoodInTheWorld(this);
		}
	}
}
