// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SnakeHUDBase.generated.h"

UCLASS()
class FINALSNAKEUE5_API ASnakeHUDBase : public AHUD
{
	GENERATED_BODY()
	
public:
	ASnakeHUDBase();

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> UIDuringTheGameClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> UIGameOverClass;

public:

	UFUNCTION()
	void AddNewGameOverWidget();
};
