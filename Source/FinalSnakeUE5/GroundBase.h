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
	void SpawnFood();

	void ToggleCollisionWall();

	// Functions for softWall
	void SpawnFoodFromTheSoftWall(const int index);

	void ChangeSoftWall(const FVector location, const FVector scale);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	// Declaring private variables
	UPROPERTY()
	TArray<FVector> worldSectors;

	// Declaring private functions
	void DivideTheWorldIntoSectors();

	FVector RandomValue();
};
