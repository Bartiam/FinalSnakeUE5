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
			float chanceToLoseBodyPart = FMath::RandRange(0.f, 1.f);

			if (chanceToLoseBodyPart <= 0.5f)
				snake->AddSnakeElements();
			else
			{
				snake->DeleteSnakeElement();
				snake->SlowDownSnake((secondsBonusValidity * 2), speedChangesOn);
			}

			groundOwner->DestroyFoodInTheWorld(this);
		}
	}
}
