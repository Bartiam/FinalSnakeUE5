// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "SnakeHUDBase.h"
#include "SnakePawnBase.h"

void ASnakeGameModeBase::BonusLevel()
{ UGameplayStatics::OpenLevel(this, TEXT("SnakeBonusLevel")); }

void ASnakeGameModeBase::GameOver()
{
	auto gameOverHUD = Cast<ASnakeHUDBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ASnakeHUDBase::StaticClass()));
	gameOverHUD->AddNewGameOverWidget();

	auto pawn = Cast<ASnakePawnBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ASnakePawnBase::StaticClass()));
	pawn->bIsGameOver = true;
}
