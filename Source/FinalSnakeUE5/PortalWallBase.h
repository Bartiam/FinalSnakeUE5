// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WallBase.h"
#include "PortalWallBase.generated.h"

/**
 * 
 */
UCLASS()
class FINALSNAKEUE5_API APortalWallBase : public AWallBase
{
	GENERATED_BODY()
	
	virtual void Interact(AActor* interactor, bool bIsHead) override;
};
