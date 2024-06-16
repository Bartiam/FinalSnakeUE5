// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FoodBase.h"
#include "BonusFoodAccelerationBase.generated.h"

/**
 * 
 */
UCLASS()
class FINALSNAKEUE5_API ABonusFoodAccelerationBase : public AFoodBase
{
	GENERATED_BODY()
	
private:
	virtual void Interact(AActor* interactor, bool bIsHead) override;
};
