// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodFromTheWallBase.h"
#include "SnakeBase.h"
#include "GroundBase.h"
#include "SnakeGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void AFoodFromTheWallBase::Interact(AActor* interactor, bool bIsHead)
{
	if (IsValid(interactor))
	{
		auto snake = Cast<ASnakeBase>(interactor);
		if (IsValid(snake))
		{
			snake->AddSnakeElements(4);
			groundOwner->DestroyFoodInTheWorld(this);
		}
	}
}
