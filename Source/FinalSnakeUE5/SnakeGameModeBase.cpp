// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "SnakeHUDBase.h"

void ASnakeGameModeBase::BonusLevel()
{ UGameplayStatics::OpenLevel(this, TEXT("SnakeBonusLevel")); }

void ASnakeGameModeBase::GameOver()
{
	auto currentHUD = Cast<ASnakeHUDBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ASnakeHUDBase::StaticClass()));
	currentHUD->AddNewGameOverWidget();
}
