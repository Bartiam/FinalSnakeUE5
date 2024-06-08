// Fill out your copyright notice in the Description page of Project Settings.


#include "SoftWallBase.h"
#include "SnakeBase.h"
#include "FoodBase.h"

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
				SpawnNewFood(location);
				--counter;
			}
			else
				DestroySoftWallAndSpawnNewWallBase();
		}
	}
}

void ASoftWallBase::SpawnNewFood(const FVector location)
{
	auto newFood = GetWorld()->SpawnActor<AFoodBase>(foodClass, FTransform(location));
}

void ASoftWallBase::DestroySoftWallAndSpawnNewWallBase()
{
	FVector location = GetActorLocation();
	
	Destroy();
}
