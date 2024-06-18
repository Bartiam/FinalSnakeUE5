// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalWallBase.h"
#include "SnakeBase.h"

void APortalWallBase::Interact(AActor* interactor, bool bIsHead)
{
	if (IsValid(interactor))
	{
		auto snake = Cast<ASnakeBase>(interactor);
		if (IsValid(snake))
		{
			snake->teleportSnake();

			float checkChanceLoseSnakeElement = FMath::RandRange(0.f, 1.f);

			if (checkChanceLoseSnakeElement > 0.8f)
			{
				snake->SlowDownSnake(5.0f, 0.1f);
				snake->DeleteSnakeElement();
			}
				
		}
	}
}
