// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SnakeGameModeBase.generated.h"

UCLASS()
class FINALSNAKEUE5_API ASnakeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	void BonusLevel();

	void GameOver();
};
