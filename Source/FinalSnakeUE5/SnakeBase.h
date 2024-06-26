// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "SnakeBase.generated.h"

class ASnakeElementBase;
class AGroundBase;

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
	void DeleteSnakeElement();
	//////////
	
	// Getters
	EMovementDirection GetLastMoveDir() const;
	bool GetSnakeCanMove() const;
	const TArray<ASnakeElementBase*> GetFullSnakeElements() const;
	const FVector GetSnakeElementLocation(int index);
	int32 GetNumbersOfSnakeElements();
	const float GetPadding() const;
	int32 GetScores() const;
	//////////

	// Declaring public functions

	void SnakeElementOverlap(ASnakeElementBase* overlappedComp, AActor* other);

	void ThePlayerLost();

	void AddSnakeElements(int count = 1);

	void StepBack();

	void teleportSnake();

	void SlowDownSnake(const float& howManySeconds, const float& speedChange);

	void SpeedUpSnake(const float& howManySeconds, const float& speedChange);

	// Declaring public variebles
	UPROPERTY(BlueprintReadWrite, Category = "World")
	AGroundBase* mainWorld;

	FTimerHandle timerForDead;
	
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

	const float initialStepIn = 0.2f;

	float currentStepIn;

	const float maxSpeedStepIn = 0.1f;

	const float minSpeedStepIn = 0.3f;

	int32 scores;

	bool bSnakeCanMove;

	UPROPERTY()
	TArray<ASnakeElementBase*> snakeElements;

	EMovementDirection lastMoveDir;

	int32 initialSizeSnake;

	bool bIsPassingThroughWall;
	///////////////////////////////

	// Declaring private functions

	void CancellationBonus();

	void MoveSnake();

	UPROPERTY()
	FVector lastPosition;
	UPROPERTY()
	FVector previousLastPosition;

	FVector LocationNewElement();
	FVector LocationNewElementMoreOne(const FVector& locationLastElement, const FVector& penultimateElement);

	void TimeToStarveToDeath();
};
