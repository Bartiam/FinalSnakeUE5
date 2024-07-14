// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeHUDBase.h"
#include "Blueprint/UserWidget.h"

ASnakeHUDBase::ASnakeHUDBase() : Super()
{
	ConstructorHelpers::FClassFinder<UUserWidget> WBP_UIDuringTheGame(TEXT("/Game/Blueprints/UI/WBP_UIDuringTheGame"));
	UIDuringTheGameClass = WBP_UIDuringTheGame.Class;
}

void ASnakeHUDBase::BeginPlay()
{
	Super::BeginPlay();
}

void ASnakeHUDBase::AddNewGameOverWidget()
{
	auto gameOverWidget = CreateWidget(GetWorld(), UIGameOverClass);

	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

	gameOverWidget->AddToViewport();
}

void ASnakeHUDBase::AddNewYouWonWidget()
{
	auto touWonWidget = CreateWidget(GetWorld(), UIYouWonClass);

	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

	touWonWidget->AddToViewport();
}