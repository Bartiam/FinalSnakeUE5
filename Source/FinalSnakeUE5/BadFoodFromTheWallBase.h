// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FoodFromTheWallBase.h"
#include "BadFoodFromTheWallBase.generated.h"

/**
 * 
 */
UCLASS()
class FINALSNAKEUE5_API ABadFoodFromTheWallBase : public AFoodFromTheWallBase
{
	GENERATED_BODY()
	
private:
	virtual void Interact(AActor* interactor, bool bIsHead) override;
};
