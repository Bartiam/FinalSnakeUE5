// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


#include "SnakeBase.generated.h"

class ASnakeElementBase;

UENUM()
enum class EMovementDirection
{
	UP, 
	DOWN, 
	LEFT, 
	RIGHT
};

UCLASS()
class FINALSNAKEUE5_API ASnakeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeBase();

	// Setters
	void SetLastMoveDir(EMovementDirection moveDir);
	void SetSnakeCanMove(bool snakeCanMove);
	//////////
	
	// Getters
	EMovementDirection GetLastMoveDir() const;
	bool GetSnakeCanMove() const;
	const TArray<ASnakeElementBase*> GetFullSnakeElements() const;
	//////////

	// Declaring public functions

	void SnakeElementOverlap(ASnakeElementBase* overlappedComp, AActor* other);

	void DestroyFullSnakeElements();

	void AddSnakeElements(int count = 1);

	void StepBack();

	void teleportSnake();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Declaring private variables
	UPROPERTY(EditDefaultsOnly, Category = "Snake elements")
	TSubclassOf<ASnakeElementBase> snakeELementClass;

	UPROPERTY(EditDefaultsOnly)
	float padding;

	UPROPERTY()
	float stepIn;

	bool bSnakeCanMove;

	UPROPERTY()
	TArray<ASnakeElementBase*> snakeElements;

	UPROPERTY()
	EMovementDirection lastMoveDir;

	int32 initialSizeSnake;
	///////////////////////////////

	// Declaring private functions

	void MoveSnake();

	UPROPERTY()
	FVector lastPosition;
	UPROPERTY()
	FVector previousLastPosition;
};
