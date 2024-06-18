// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusPortalBase.h"
#include "SnakeBase.h"

void ABonusPortalBase::Interact(AActor* interactor, bool bIsHead)
{
	if (IsValid(interactor))
	{
		auto snake = Cast<ASnakeBase>(interactor);
		if (IsValid(snake))
		{
			snake->ChangeLevel();
		}
	}
}
