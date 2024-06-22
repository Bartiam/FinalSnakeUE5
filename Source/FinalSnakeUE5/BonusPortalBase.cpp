// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusPortalBase.h"
#include "SnakeBase.h"
#include "SnakeGameModeBase.h"
#include "Kismet/GameplayStatics.h"


void ABonusPortalBase::Interact(AActor* interactor, bool bIsHead)
{
	if (IsValid(interactor))
	{
		ASnakeGameModeBase* gameMode = Cast<ASnakeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		if (IsValid(gameMode))
		{
			gameMode->BonusLevel();
		}
	}
}
