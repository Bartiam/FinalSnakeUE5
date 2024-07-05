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
				for (int i = 0; i < 2; ++i)
					snake->SlowDownSnake(10.f, 0.15f);

				snake->DeleteSnakeElement();
			}
				
		}
	}
}
