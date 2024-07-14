// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeBase.generated.h"

class ASnakeElementBase;
class AGroundBase;
class AFoodBase;

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
	void SetSkill(AFoodBase* newSkill);
	void SetPreviousDirectionOfTravel(EMovementDirection PrevDir);
	//////////
	
	// Getters
	EMovementDirection GetLastMoveDir() const;
	bool GetSnakeCanMove() const;
	TArray<ASnakeElementBase*> GetFullSnakeElements() const;
	const FVector GetSnakeElementLocation(int index);
	const int32 GetNumbersOfSnakeElements() const;
	const float GetPadding() const;
	int32 GetScores() const;
	AFoodBase* GetSkill() const;
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UTexture* defaultIcon;

	UPROPERTY(BlueprintReadWrite, Category = "World")
	AGroundBase* mainWorld;

	FTimerHandle timerForDead;

	UPROPERTY(EditDefaultsOnly, Category = "Snake elements")
	TSubclassOf<ASnakeElementBase> snakeELementClass;

	bool bIsYouWon;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Declaring private variables

	UPROPERTY(EditDefaultsOnly)
	float padding;

	const float initialStepIn = 0.25f;

	float currentStepIn;

	const float maxSpeedStepIn = 0.1f;

	const float minSpeedStepIn = 0.4f;

	int32 scores;

	bool bSnakeCanMove;

	UPROPERTY()
	TArray<ASnakeElementBase*> snakeElements;

	EMovementDirection lastMoveDir;

	EMovementDirection previousDirectionOfTravel;

	int32 initialSizeSnake;

	bool bIsPassingThroughWall;
	///////////////////////////////

	// Private timers for gameplay

	FTimerHandle timerSlowDownSnake;
	FTimerHandle timerSpeedUpSnake;

	//////////////////////////////

	// Declaring private functions

	void CancellationBonus();

	void MoveSnake();

	void SetSnakeElementsAssets();

	void SetsTheOldDirectionOfTravel();

	UPROPERTY()
	FVector lastPosition;
	UPROPERTY()
	FVector previousLastPosition;

	UPROPERTY()
	FRotator lastElemRotation;

	UPROPERTY()
	FRotator previousElemRotation;

	UPROPERTY()
	AFoodBase* skill;

	FRotator RotationNewElement();
	FVector LocationNewElement();
	FVector LocationNewElementMoreOne(const FVector& locationLastElement, const FVector& penultimateElement);

	void TimeToStarveToDeath();
};
