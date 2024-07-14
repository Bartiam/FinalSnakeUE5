// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "SnakeHUDBase.h"
#include "SnakePawnBase.h"

void ASnakeGameModeBase::GameOver()
{
	auto gameOverHUD = Cast<ASnakeHUDBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ASnakeHUDBase::StaticClass()));
	gameOverHUD->AddNewGameOverWidget();

	auto snakePawn = Cast<ASnakePawnBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ASnakePawnBase::StaticClass()));
	snakePawn->bIsGameOver = true;
}

void ASnakeGameModeBase::YouWon()
{
	auto snake = Cast<ASnakeBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ASnakeBase::StaticClass()));
	snake->bIsYouWon = true;

	auto youWonHUD = Cast<ASnakeHUDBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ASnakeHUDBase::StaticClass()));
	youWonHUD->AddNewYouWonWidget();
}