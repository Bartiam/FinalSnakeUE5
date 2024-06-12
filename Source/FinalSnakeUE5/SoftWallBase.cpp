// Fill out your copyright notice in the Description page of Project Settings.


#include "SoftWallBase.h"
#include "SnakeBase.h"
#include "FoodBase.h"
#include "GroundBase.h"

void ASoftWallBase::BeginPlay()
{
	Super::BeginPlay();

	counter = FMath::RandRange(1, 3);
}

void ASoftWallBase::Interact(AActor* interactor, bool bIsHead)
{
	if (IsValid(interactor))
	{
		auto snake = Cast<ASnakeBase>(interactor);
		if (IsValid(snake))
		{
			const FVector location = snake->GetSnakeElementLocation(1);
			snake->StepBack();
			if (counter > 0)
			{
				float randInt = FMath::RandRange(0.f, 1.f);
				if (randInt >= 0.5f)
				{
					randInt = FMath::RandRange(0.f, 1.f);
					if (randInt <= 0.33f)
						groundOwner->SpawnFoodFromTheSoftWall(int(EFoodsEnum::GoodFood));
					else if (randInt <= 0.66f)
						groundOwner->SpawnFoodFromTheSoftWall(int(EFoodsEnum::BadFood));
					else 
						groundOwner->SpawnFoodFromTheSoftWall(int(EFoodsEnum::BonusFood));
				}
				--counter;
			}
			else
				Destroy();
		}
	}
}
