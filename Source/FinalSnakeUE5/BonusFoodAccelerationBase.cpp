// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusFoodAccelerationBase.h"
#include "SnakeBase.h"
#include "GroundBase.h"

FString ABonusFoodAccelerationBase::GetNameOfSkill()
{ return FString(TEXT("Acceleration speed")); }

void ABonusFoodAccelerationBase::Interact(AActor* interactor, bool bIsHead)
{
	if (IsValid(interactor))
	{
		auto snake = Cast<ASnakeBase>(interactor);
		if (IsValid(snake))
		{
			if (IsValid(snake->GetSkill()))
			{
				snake->SpeedUpSnake(secondsBonusValidity, speedChangesOn);
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
