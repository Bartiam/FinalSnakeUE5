// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundBase.generated.h"

class AWallBase;
class UStaticMeshComponent;
class AFoodBase;
class ASnakeBase;

UCLASS()
class FINALSNAKEUE5_API AGroundBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGroundBase();

	// Getters
	TArray<FVector> GetFullSectors() const;
	const FVector GetOneSector(int index) const;
	const int32 GetSizeOfSectors() const;

	// Getters for UI blueprints
	int32 GetWorldSecotrs();

	// World Size Variables
	UPROPERTY(EditDefaultsOnly, Category = "SIZES")
	float minPositionX;
	UPROPERTY(EditDefaultsOnly, Category = "SIZES")
	float minPositionY;
	UPROPERTY(EditDefaultsOnly, Category = "SIZES")
	float maxPositionX;
	UPROPERTY(EditDefaultsOnly, Category = "SIZES")
	float maxPositionY;

	// Declaring public variables
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UStaticMeshComponent* meshComponent;

	UPROPERTY(BlueprintReadWrite)
	AFoodBase* food;

	UPROPERTY(EditDefaultsOnly, Category = "food")
	TArray<TSubclassOf<AFoodBase>> foodClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Walls")
	TArray<TSubclassOf<AWallBase>> wallsClasses;

	// Declaring public functions
	void DestroyFoodInTheWorld(AFoodBase* currentFood);

	void SpawnFood(const ASnakeBase* snake);

	void ToggleCollisionWall();

	void SpawnWallsAgainstSnake(const ASnakeBase* snake);

	void SoftWallDestroy(AWallBase* wall);

	void BonusFoodSpawn(const ASnakeBase* snake, const int& typeOfFood);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	// Private timers for gameplay
	FTimerHandle timeToWalkThroughWalls;

	// Declaring private variables
	UPROPERTY()
	TArray<FVector> worldSectors;

	TArray<TArray<AWallBase*>> wallsToSpawnAgainstSnake;

	TArray<AWallBase*> wallsToSpawnBeginPlay;

	bool bIsToggleToSpawnWall;

	// Variables for spawn wall in begin play
	UPROPERTY(EditDefaultsOnly, Category = "Location Wall")
	TArray<FVector> locationsOfWallToBeginPlay;

	TArray<AFoodBase*> foodsInTheWorld;

	// Declaring private functions
	void DivideTheWorldIntoSectors();

	void SpawnWallBeginPlay();

	FVector RandomPosition(const ASnakeBase* snake);

	bool CheckWallsInTheWorld(const FVector& currentSector);

	bool CheckPositionsSnakeElements(const ASnakeBase* snake, const FVector currentPosition);

	bool CheckPositionsFoodOfTheWorld(const FVector currentPosition);

	bool CheckPositionsWallBeginPlay(const FVector& currentPosition);

	bool IsThereWallInFrontOfTheSnakeHead(const ASnakeBase* snake);

	bool IsThereFoodOrSnakeElementOnTheSpawnWall(const ASnakeBase* snake, const FVector& currentLocationToSpawnWall);

	void CheckingArrayForNull();

	void DestroyWalls();
};
