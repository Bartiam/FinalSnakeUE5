// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SnakeGameModeBase.generated.h"

/**
 * 
 */

UENUM()
enum class EGameStates
{
	WON,
	LOSE
};

UCLASS()
class FINALSNAKEUE5_API ASnakeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	void BonusLevel();
};
