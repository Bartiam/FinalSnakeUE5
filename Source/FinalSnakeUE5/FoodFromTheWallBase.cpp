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
			int8 countNewTails = FMath::RandRange(2, 4);
			snake->AddSnakeElements(countNewTails);
			groundOwner->DestroyFoodInTheWorld(this);
		}
	}
}
