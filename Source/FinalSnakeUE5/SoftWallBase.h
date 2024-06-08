// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WallBase.h"
#include "SoftWallBase.generated.h"

/**
 * 
 */

UENUM()
enum class EFoodsEnum
{
	GoodFood = 1,
	BadFood = 2,
	BonusFood = 3
};

UCLASS()
class FINALSNAKEUE5_API ASoftWallBase : public AWallBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Food")
	TSubclassOf<class AFoodBase> foodClass;

	UPROPERTY(BlueprintReadWrite)
	class AGroundBase* groundOwner;

	virtual void Interact(AActor* interactor, bool bIsHead) override;

private:
	int8 counter;
};
