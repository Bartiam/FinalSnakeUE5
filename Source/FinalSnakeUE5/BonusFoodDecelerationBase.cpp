// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusFoodDecelerationBase.h"
#include "SnakeBase.h"
#include "GroundBase.h"

void ABonusFoodDecelerationBase::Interact(AActor* interactor, bool bIsHead)
{
	if (IsValid(interactor))
	{
		auto snake = Cast<ASnakeBase>(interactor);
		if (IsValid(snake))
		{
			if (IsValid(snake->GetSkill()))
			{
				snake->SlowDownSnake(secondsBonusValidity, speedChangesOn);
				groundOwner->DestroyFoodInTheWorld(this);
			}
			else
			{
				snake->SetSkill(this);
				FVector newLocation = FVector(GetActorLocation().X, GetActorLocation().Y, (GetActorLocation().Z - 100));

				SetActorLocation(newLocation);
			}
		}
	}
}
