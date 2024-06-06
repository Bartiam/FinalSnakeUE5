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
	TArray<FVector> GetFullSectors() const;
	const FVector GetOneSector(int index) const;
	const int32 GetSizeOfSectors() const;
	const TArray<ASnakeElementBase*> GetFullSnakeElements() const;
	//////////

	void SnakeElementOverlap(ASnakeElementBase* overlappedComp, AActor* other);

	void DestroyFullSnakeElements();

	void AddSnakeElements(int count = 1);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// World Size Variables
	UPROPERTY(EditDefaultsOnly, Category = "SIZES")
	float minPositionX;
	UPROPERTY(EditDefaultsOnly, Category = "SIZES")
	float minPositionY;
	UPROPERTY(EditDefaultsOnly, Category = "SIZES")
	float maxPositionX;
	UPROPERTY(EditDefaultsOnly, Category = "SIZES")
	float maxPositionY;

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

	UPROPERTY()
	TArray<FVector> sectors;
	///////////////////////////////

	// Declaring private functions

	void MoveSnake();

	void DivideTheWorldIntoSectors();
};
