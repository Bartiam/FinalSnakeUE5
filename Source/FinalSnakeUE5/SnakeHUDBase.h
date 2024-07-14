// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SnakeHUDBase.generated.h"

class UUserWidget;

UCLASS()
class FINALSNAKEUE5_API ASnakeHUDBase : public AHUD
{
	GENERATED_BODY()
	
public:
	ASnakeHUDBase();

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> UIDuringTheGameClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> UIGameOverClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> UIYouWonClass;

public:

	UFUNCTION()
	void AddNewGameOverWidget();

	UFUNCTION()
	void AddNewYouWonWidget();
};
