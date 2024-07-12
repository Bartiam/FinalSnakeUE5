// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FoodBase.h"
#include "BonusFoodPassageThroughWalls.generated.h"

UCLASS()
class FINALSNAKEUE5_API ABonusFoodPassageThroughWalls : public AFoodBase
{
	GENERATED_BODY()
	
public:
	virtual FString GetNameOfSkill() override;

private:
	virtual void Interact(AActor* interactor, bool bIsHead) override;
};
