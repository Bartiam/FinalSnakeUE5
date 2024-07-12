// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusFoodPassageThroughWalls.h"
#include "SnakeBase.h"
#include "GroundBase.h"

FString ABonusFoodPassageThroughWalls::GetNameOfSkill()
{ return FString(TEXT("Passage through wall")); }

void ABonusFoodPassageThroughWalls::Interact(AActor* interactor, bool bIsHead)
{
	if (IsValid(interactor))
	{
		auto snake = Cast<ASnakeBase>(interactor);
		if (IsValid(snake))
		{
			if (IsValid(snake->GetSkill()))
			{
				groundOwner->ToggleCollisionWall();
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
