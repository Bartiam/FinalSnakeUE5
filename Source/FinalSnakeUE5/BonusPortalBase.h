// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WallBase.h"
#include "BonusPortalBase.generated.h"

/**
 * 
 */
UCLASS()
class FINALSNAKEUE5_API ABonusPortalBase : public AWallBase
{
	GENERATED_BODY()
	
private:
	virtual void Interact(AActor* interactor, bool bIsHead) override;
};
