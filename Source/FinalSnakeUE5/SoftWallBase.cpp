// Fill out your copyright notice in the Description page of Project Settings.


#include "SoftWallBase.h"
#include "SnakeBase.h"

void ASoftWallBase::Interact(AActor* interactor, bool bIsHead)
{
	if (IsValid(interactor))
	{
		auto snake = Cast<ASnakeBase>(interactor);
		if (IsValid(snake))
			snake->StepBack();
	}
}
