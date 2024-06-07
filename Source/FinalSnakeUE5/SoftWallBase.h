// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WallBase.h"
#include "SoftWallBase.generated.h"

/**
 * 
 */
UCLASS()
class FINALSNAKEUE5_API ASoftWallBase : public AWallBase
{
	GENERATED_BODY()
	
public:
	virtual void Interact(AActor* interactor, bool bIsHead) override;
};
