// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FoodBase.h"
#include "FoodFromTheWallBase.generated.h"

/**
 * 
 */
UCLASS()
class FINALSNAKEUE5_API AFoodFromTheWallBase : public AFoodBase
{
	GENERATED_BODY()
	
public:
	virtual void Interact(AActor* interactor, bool bIsHead) override;
};
