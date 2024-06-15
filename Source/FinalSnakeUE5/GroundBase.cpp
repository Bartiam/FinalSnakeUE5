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
	RootComponent = meshComponent;
	countSnakeElementsForBonusLevel = 50;
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
		float wallLungeChance = FMath::RandRange(0.f, 1.f);
		int indexOfWall;
		if (wallLungeChance > 0.3f)
			indexOfWall = 0;
		else
			indexOfWall = 1;

		if (snake->GetFullSnakeElements().Num() == countSnakeElementsForBonusLevel)
		{
			countSnakeElementsForBonusLevel += 50;
			indexOfWall = 2;
		}
		FVector newPositionOfWall(currentPositionOfHeadSnake.X + (paddingX * 3), currentPositionOfHeadSnake.Y + (paddingY * 3), currentPositionOfHeadSnake.Z);
		if (newPositionOfWall.X >= minPositionX && newPositionOfWall.X <= maxPositionX &&
			newPositionOfWall.Y >= minPositionY && newPositionOfWall.Y <= maxPositionY)
		{
			AWallBase* newWall = GetWorld()->SpawnActor<AWallBase>(wallsClasses[indexOfWall], FTransform(newPositionOfWall));
			FTimerHandle tymerDelay;
			GetWorldTimerManager().SetTimer(tymerDelay, this, &AGroundBase::DestroyWalls, 5, false);
			wallsOnTheGround.Add(newWall);
			if (paddingX != 0.f)
				currentPositionOfHeadSnake.Y += snake->GetPadding();
			else 
				currentPositionOfHeadSnake.X += snake->GetPadding();
		}
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
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASnakeElementBase::StaticClass(), snakeElementsFromWorld);

	auto randomIndex = FMath::RandRange(0, GetSizeOfSectors() - 1);
	auto currentPosition = GetOneSector(randomIndex);

	while (CheckPositionsSnakeElementsAndWalls(currentPosition))
	{
		randomIndex = FMath::RandRange(0, GetSizeOfSectors() - 1);
		currentPosition = GetOneSector(randomIndex);
	}

	return currentPosition;
}

bool AGroundBase::CheckPositionsSnakeElementsAndWalls(FVector currentPosition)
{
	for (int i = 0; i < snakeElementsFromWorld.Num(); ++i)
	{
		if (currentPosition == snakeElementsFromWorld[i]->GetActorLocation())
			return true;
	}

	if (!(wallsOnTheGround.IsEmpty()))
	{
		for (int i = 0; i < wallsOnTheGround.Num(); ++i)
		{
			if (currentPosition == wallsOnTheGround[i]->GetActorLocation())
				return true;
		}
	}

	return false;
}

void AGroundBase::DestroyWalls()
{
	for (int i = 0; i < wallsOnTheGround.Num();)
	{
		wallsOnTheGround[i]->Destroy();
		wallsOnTheGround.RemoveAt(i);
	}
}
