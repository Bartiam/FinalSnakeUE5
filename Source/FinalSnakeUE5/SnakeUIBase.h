// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SnakeUIBase.generated.h"

/**
 * 
 */
UCLASS()
class FINALSNAKEUE5_API USnakeUIBase : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetCurrentTimeToDead();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetCurrentScores();
};
