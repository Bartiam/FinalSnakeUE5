// Fill out your copyright notice in the Description page of Project Settings.


#include "GroundBase.h"
#include "WallBase.h"
#include "Components/StaticMeshComponent.h"
#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "FoodBase.h"
#include "Kismet/GameplayStatics.h"

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
	for (int i = 0; i < 10; i++)
	{
		AFoodBase* newFood = GetWorld()->SpawnActor<AFoodBase>(foodClasses[0], FTransform(RandomPositionOfFood()));
	}
	food = GetWorld()->SpawnActor<AFoodBase>(foodClasses[0], FTransform(RandomPositionOfFood()));
	food->groundOwner = this;
}

// Called every frame
void AGroundBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AGroundBase::DivideTheWorldIntoSectors()
{
	for (float i = minPositionX; i <= maxPositionX; i += 60.f)
	{
		for (float j = minPositionY; j <= maxPositionY; j += 60.f)
		{
			worldSectors.Add(FVector(i, j, 30.f));
		}
	}
}

void AGroundBase::SpawnFood()
{
	food->SetActorLocation(RandomPositionOfFood());
}

void AGroundBase::ToggleCollisionWall()
{
	
}

void AGroundBase::SpawnWallsAgainstSnake(const ASnakeBase* snake)
{
	FVector currentPositionOfHeadSnake = snake->GetFullSnakeElements()[0]->GetActorLocation();
	float paddingX = 0, paddingY = 0;
	EMovementDirection currentDirection = snake->GetLastMoveDir();

	switch (currentDirection)
	{
	case EMovementDirection::UP:
		currentPositionOfHeadSnake.Y -= snake->GetPadding();
		paddingX = snake->GetPadding();
		break;
	case EMovementDirection::DOWN:
		currentPositionOfHeadSnake.Y -= snake->GetPadding();
		paddingX = (snake->GetPadding() * -1);
		break;
	case EMovementDirection::LEFT:
		currentPositionOfHeadSnake.X -= snake->GetPadding();
		paddingY = (snake->GetPadding() * -1);
		break;
	case EMovementDirection::RIGHT:
		currentPositionOfHeadSnake.X -= snake->GetPadding();
		paddingY = snake->GetPadding();
		break;
	}

	for (int i = 0; i < 3; ++i)
	{
		FVector newPositionOfWall(currentPositionOfHeadSnake.X + (paddingX * 3), currentPositionOfHeadSnake.Y + (paddingY * 3), currentPositionOfHeadSnake.Z);
		auto newWall = GetWorld()->SpawnActor<AWallBase>(wallsClasses[0], FTransform(newPositionOfWall));
		if (paddingX != 0.f)
			currentPositionOfHeadSnake.Y += snake->GetPadding();
		else 
			currentPositionOfHeadSnake.X += snake->GetPadding();
	}
}

// Functions for softWall
void AGroundBase::SpawnFoodFromTheSoftWall(const int index) 
{
										//	index = 1 - GoodFood; index = 2 - Badfood; index = 3 - BonusFood;
	auto newFoodFromTheWall = GetWorld()->SpawnActor<AFoodBase>(foodClasses[index], FTransform(RandomPositionOfFood()));
}

FVector AGroundBase::RandomPositionOfFood()
{
	TArray<AActor*> snakeElements;
	TArray<AActor*> walls;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWallBase::StaticClass(), walls);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASnakeElementBase::StaticClass(), snakeElements);

	auto randomIndex = FMath::RandRange(0, GetSizeOfSectors() - 1);
	auto currentPosition = GetOneSector(randomIndex);

	

	while (CheckPositionsSnakeElementsAndWalls(snakeElements, currentPosition) ||
			CheckPositionsSnakeElementsAndWalls(walls, currentPosition))
	{
		randomIndex = FMath::RandRange(0, GetSizeOfSectors() - 1);
		currentPosition = GetOneSector(randomIndex);
	}

	return currentPosition;
}

bool AGroundBase::CheckPositionsSnakeElementsAndWalls(const TArray<AActor*> elements, FVector currentPosition)
{
	for (int i = 0; i < elements.Num(); ++i)
	{
		
	}

	return false;
}
