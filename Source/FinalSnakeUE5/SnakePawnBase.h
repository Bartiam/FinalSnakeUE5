// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "SnakeBase.h"



#include "SnakePawnBase.generated.h"

UCLASS()
class FINALSNAKEUE5_API ASnakePawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASnakePawnBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// Declaring private variables
	UPROPERTY(VisibleDefaultsOnly, Category = "Camera")
	UCameraComponent* mainCamera;

	UPROPERTY()
	ASnakeBase* snakeActor;

	UPROPERTY(EditDefaultsOnly, Category = "Main snake character")
	TSubclassOf<ASnakeBase> snakeActorClass;

	// Declaring private functions
	void CreateSnakeActor();
};
