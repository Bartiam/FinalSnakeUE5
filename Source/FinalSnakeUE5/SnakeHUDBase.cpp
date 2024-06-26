// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeHUDBase.h"
#include "Blueprint/UserWidget.h"

ASnakeHUDBase::ASnakeHUDBase() : Super()
{
	ConstructorHelpers::FClassFinder<UUserWidget> WBP_UI(TEXT("/Game/Blueprints/UI/WBP_UIDuringTheGame"));

	userWidgetClass = WBP_UI.Class;
}

void ASnakeHUDBase::BeginPlay()
{
	Super::BeginPlay();
}
