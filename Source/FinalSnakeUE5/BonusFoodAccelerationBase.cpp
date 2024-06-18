// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusFoodAccelerationBase.h"
#include "SnakeBase.h"

void ABonusFoodAccelerationBase::Interact(AActor* interactor, bool bIsHead)
{
	if (IsValid(interactor))
	{
		auto snake = Cast<ASnakeBase>(interactor);
		if (IsValid(snake))
		{
			snake->SpeedUpSnake(secondsBonusValidity, speedChangesOn);
			Destroy();
		}
	}
}
