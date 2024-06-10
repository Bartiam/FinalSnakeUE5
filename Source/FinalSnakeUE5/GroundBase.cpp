// Fill out your copyright notice in the Description page of Project Settings.


#include "GroundBase.h"
#include "WallBase.h"
#include "Components/StaticMeshComponent.h"
#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "FoodBase.h"

// Sets default values
AGroundBase::AGroundBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ground"));
}

// Getters
TArray<FVector> AGroundBase::GetFullSectors() const
{ return worldSectors; }

const FVector AGroundBase::GetOneSector(int index) const
{ return worldSectors[index]; }

const int32 AGroundBase::GetSizeOfSectors() const
{ return worldSectors.Num(); }

// Called when the game starts or when spawned
void AGroundBase::BeginPlay()
{
	Super::BeginPlay();
	DivideTheWorldIntoSectors();
	food = GetWorld()->SpawnActor<AFoodBase>(foodClasses[0], FTransform(worldSectors[300]));
	food->groundOwner = this;
}

// Called every frame
void AGroundBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AGroundBase::FindsSectorsAroundFood()
{
	FVector currentPositionOfFood = food->GetActorLocation();

	for (int i = 0; i < currentPositionOfFood.X; i++)
	{

	}
}

void AGroundBase::DivideTheWorldIntoSectors()
{
	for (float i = minPositionX; i <= maxPositionX; i += 60.f)
	{
		for (float j = minPositionY; j <= maxPositionY; j += 60.f)
		{
			worldSectors.Add(FVector(i, j, 20.f));
		}
	}
}

void AGroundBase::SpawnWallsAgainstSnake(ASnakeBase* snake, const int& numberMovesBeforeFood)
{
	FindsSectorsAroundFood();
	snake->SetWallSpawnSwitch(false);
}

void AGroundBase::SpawnFood(const ASnakeBase* snake)
{
	food->SetActorLocation(RandomValue(snake));
}

void AGroundBase::ToggleCollisionWall()
{

}

// Functions for softWall
void AGroundBase::SpawnFoodFromTheSoftWall(const ASnakeBase* snake, const int index) 
{
											//	index = 1 - GoodFood; index = 2 - Badfood; index = 3 - BonusFood;
	auto newFoodFromTheWall = GetWorld()->SpawnActor<AFoodBase>(foodClasses[index], FTransform(RandomValue(snake)));
}

void AGroundBase::ChangeSoftWall(const FVector location, const FVector scale)
{
	auto newWallBase = GetWorld()->SpawnActor<AWallBase>(wallsClasses[0], FTransform(location));
	newWallBase->SetActorScale3D(scale);
}

FVector AGroundBase::RandomValue(const ASnakeBase* snake) const
{
	auto randomIndex = FMath::RandRange(0, GetSizeOfSectors() - 1);
	auto snakeElements = snake->GetFullSnakeElements();
	auto currentPosition = GetOneSector(randomIndex);

	for (int i = 0; i < snakeElements.Num(); ++i)
	{
		if (currentPosition == snakeElements[i]->GetActorLocation())
		{
			i = 0;
			randomIndex = FMath::RandRange(0, GetSizeOfSectors() - 1);
			currentPosition = GetOneSector(randomIndex);
		}
	}

	return currentPosition;
}
