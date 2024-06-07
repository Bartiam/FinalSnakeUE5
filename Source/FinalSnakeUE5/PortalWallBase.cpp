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
		}
	}
}
