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
	bIsToggleToSpawnWall = false;
}

// Getters
TArray<FVector> AGroundBase::GetFullSectors() const
{ return worldSectors; }

const FVector AGroundBase::GetOneSector(int index) const
{ return worldSectors[index]; }

const int32 AGroundBase::GetSizeOfSectors() const
{ return worldSectors.Num(); }

int32 AGroundBase::GetWorldSecotrs()
{ return worldSectors.Num(); }

// Called when the game starts or when spawned
void AGroundBase::BeginPlay()
{
	Super::BeginPlay();
	SpawnWallBeginPlay();
	DivideTheWorldIntoSectors();
	ASnakeBase* snake = Cast<ASnakeBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ASnakeBase::StaticClass()));
	food = GetWorld()->SpawnActor<AFoodBase>(foodClasses[0], FTransform(RandomPosition(snake)));
	food->groundOwner = this;
	foodsInTheWorld.Add(food);
}

// Called every frame
void AGroundBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGroundBase::DestroyFoodInTheWorld(AFoodBase* foodToDelete)
{
	foodsInTheWorld.RemoveSingle(foodToDelete);
	foodToDelete->Destroy();
}

void AGroundBase::DivideTheWorldIntoSectors()
{
	for (float i = minPositionX; i <= maxPositionX; i += 60.f)
	{
		for (float j = minPositionY; j <= maxPositionY; j += 60.f)
		{
			if (!(CheckWallsInTheWorld(FVector(i, j, 30.f))))
				worldSectors.Add(FVector(i, j, 30.f));
		}
	}
}

void AGroundBase::SpawnWallBeginPlay()
{
	for (int i = 0; i < locationsOfWallToBeginPlay.Num(); ++i)
	{
		AWallBase* newWall;
		if (locationsOfWallToBeginPlay[i].X == -330.f && locationsOfWallToBeginPlay[i].Y >= -90.f && locationsOfWallToBeginPlay[i].Y <= 90.f)
			newWall = GetWorld()->SpawnActor<AWallBase>(wallsClasses[1], FTransform(locationsOfWallToBeginPlay[i]));
		else if (locationsOfWallToBeginPlay[i].Y == -690.f && locationsOfWallToBeginPlay[i].X <= 510.f && locationsOfWallToBeginPlay[i].X >= 390.f)
			newWall = GetWorld()->SpawnActor<AWallBase>(wallsClasses[1], FTransform(locationsOfWallToBeginPlay[i]));
		else if (locationsOfWallToBeginPlay[i].Y == 690.f && locationsOfWallToBeginPlay[i].X <= -390.f && locationsOfWallToBeginPlay[i].X >= -510.f)
			newWall = GetWorld()->SpawnActor<AWallBase>(wallsClasses[1], FTransform(locationsOfWallToBeginPlay[i]));
		else if (locationsOfWallToBeginPlay[i].Y == -690 && locationsOfWallToBeginPlay[i].X <= -90 && locationsOfWallToBeginPlay[i].X >= -210)
			newWall = GetWorld()->SpawnActor<AWallBase>(wallsClasses[1], FTransform(locationsOfWallToBeginPlay[i]));
		else if (locationsOfWallToBeginPlay[i].Y == 690 && locationsOfWallToBeginPlay[i].X >= 90 && locationsOfWallToBeginPlay[i].X <= 210)
			newWall = GetWorld()->SpawnActor<AWallBase>(wallsClasses[1], FTransform(locationsOfWallToBeginPlay[i]));
		else
			newWall = GetWorld()->SpawnActor<AWallBase>(wallsClasses[0], FTransform(locationsOfWallToBeginPlay[i]));
		wallsToSpawnBeginPlay.Add(newWall);
	}
}

void AGroundBase::SpawnFood(const ASnakeBase* snake)
{ food->SetActorLocation(RandomPosition(snake)); }

void AGroundBase::ToggleCollisionWall()
{
	GetWorldTimerManager().ClearTimer(timeToWalkThroughWalls);

	if (!(wallsToSpawnAgainstSnake.IsEmpty()))
	{
		for (int i = 0; i < wallsToSpawnAgainstSnake.Num(); ++i)
		{
			for (int j = 0; j < wallsToSpawnAgainstSnake[i].Num(); ++j)
			{
				if (wallsToSpawnAgainstSnake[i][j]->meshComponent->GetCollisionEnabled() == ECollisionEnabled::NoCollision)
					wallsToSpawnAgainstSnake[i][j]->meshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
				else
					wallsToSpawnAgainstSnake[i][j]->meshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			}
		}
	}

	for (int i = 0; i < wallsToSpawnBeginPlay.Num(); ++i)
	{
		if (wallsToSpawnBeginPlay[i]->meshComponent->GetCollisionEnabled() == ECollisionEnabled::NoCollision)
			wallsToSpawnBeginPlay[i]->meshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		else
			wallsToSpawnBeginPlay[i]->meshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	if (wallsToSpawnBeginPlay[0]->meshComponent->GetCollisionEnabled() == ECollisionEnabled::QueryOnly)
		bIsToggleToSpawnWall = false;

	if (wallsToSpawnBeginPlay[0]->meshComponent->GetCollisionEnabled() == ECollisionEnabled::NoCollision)
	{
		bIsToggleToSpawnWall = true;
		GetWorldTimerManager().SetTimer(timeToWalkThroughWalls, this, &AGroundBase::ToggleCollisionWall, 5, false);
	}
}

void AGroundBase::SpawnWallsAgainstSnake(const ASnakeBase* snake)
{
	FVector currentPositionOfHeadSnake = snake->GetFullSnakeElements()[0]->GetActorLocation();
	float paddingX = 0, paddingY = 0;
	EMovementDirection currentDirection = snake->GetLastMoveDir();
	float wallLungeChance;
	int indexOfWall;

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

	TArray<AWallBase*> tempWallsForAdd;

	wallLungeChance = FMath::RandRange(0.f, 1.f);

	if (!IsThereWallInFrontOfTheSnakeHead(snake))
		return;

	for (int i = 0; i < 3; ++i)
	{
		wallLungeChance = FMath::RandRange(0.f, 1.f);
		indexOfWall = 0;

		if (wallLungeChance < 0.90f && wallLungeChance > 0.45f)
			indexOfWall = 1;

		FVector newPositionOfWall(currentPositionOfHeadSnake.X + (paddingX * 2), currentPositionOfHeadSnake.Y + (paddingY * 2), currentPositionOfHeadSnake.Z);

		if (newPositionOfWall.X >= minPositionX && newPositionOfWall.X <= maxPositionX &&
			newPositionOfWall.Y >= minPositionY && newPositionOfWall.Y <= maxPositionY &&
			IsThereFoodOrSnakeElementOnTheSpawnWall(snake, newPositionOfWall) && 
			CheckPositionsWallBeginPlay(newPositionOfWall))
		{
										// indexOfWall == 0: WallBase; indexOfWall == 1: SoftWall; indexOfWall == 2: BonusPortal;
			AWallBase* newWall = GetWorld()->SpawnActor<AWallBase>(wallsClasses[indexOfWall], FTransform(newPositionOfWall));

			if (bIsToggleToSpawnWall)
				newWall->meshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			tempWallsForAdd.Add(newWall);
		}

		if (paddingX != 0.f)
			currentPositionOfHeadSnake.Y += snake->GetPadding();
		else
			currentPositionOfHeadSnake.X += snake->GetPadding();
	}
	wallsToSpawnAgainstSnake.Add(tempWallsForAdd);
	CheckingArrayForNull();

	FTimerHandle tymerDelay;
	GetWorldTimerManager().SetTimer(tymerDelay, this, &AGroundBase::DestroyWalls, 20, false);
}

void AGroundBase::BonusFoodSpawn(const ASnakeBase* snake, const int& typeOfFood)
{
	auto newFood = GetWorld()->SpawnActor<AFoodBase>(foodClasses[typeOfFood], FTransform(RandomPosition(snake)));
	newFood->groundOwner = this;
	foodsInTheWorld.Add(newFood);
}

FVector AGroundBase::RandomPosition(const ASnakeBase* snake)
{
	auto randomIndex = FMath::RandRange(0, GetSizeOfSectors() - 1);
	auto currentPosition = GetOneSector(randomIndex);

	while (CheckPositionsSnakeElements(snake, currentPosition) ||
		CheckPositionsFoodOfTheWorld(currentPosition))
	{
		randomIndex = FMath::RandRange(0, GetSizeOfSectors() - 1);
		currentPosition = GetOneSector(randomIndex);
	}

	return currentPosition;
}

bool AGroundBase::CheckWallsInTheWorld(const FVector& currentSector)
{
	for (int i = 0; i < locationsOfWallToBeginPlay.Num(); ++i)
	{
		if (locationsOfWallToBeginPlay[i] == currentSector)
			return true;
	}

	return false;
}

bool AGroundBase::CheckPositionsSnakeElements(const ASnakeBase* snake, FVector currentPosition)
{
	auto snakeElements = snake->GetFullSnakeElements();

	for (int i = 0; i < snakeElements.Num(); ++i)
	{
		if (currentPosition == snakeElements[i]->GetActorLocation())
			return true;
	}

	return false;
}

bool AGroundBase::CheckPositionsFoodOfTheWorld(const FVector currentPosition)
{
	for (int i = 0; i < foodsInTheWorld.Num(); ++i)
	{
		if (currentPosition == foodsInTheWorld[i]->GetActorLocation())
			return true;
	}

	return false;
}

bool AGroundBase::CheckPositionsWallBeginPlay(const FVector& currentPosition)
{
	for (int i = 0; i < wallsToSpawnBeginPlay.Num(); ++i)
	{
		if (wallsToSpawnBeginPlay[i]->GetActorLocation() == currentPosition)
			return false;
	}

	return true;
}

void AGroundBase::CheckingArrayForNull()
{
	for (int i = 0; i < wallsToSpawnAgainstSnake.Num(); ++i)
	{
		if (wallsToSpawnAgainstSnake[i].IsEmpty())
			wallsToSpawnAgainstSnake.RemoveAt(i);
	}
}

void AGroundBase::SoftWallDestroy(AWallBase* wall)
{
	for (int i = 0; i < locationsOfWallToBeginPlay.Num(); ++i)
	{
		if (locationsOfWallToBeginPlay[i] == wall->GetActorLocation())
		{
			locationsOfWallToBeginPlay.RemoveAt(i);
			break;
		}
	}

	for (int i = 0; i < wallsToSpawnAgainstSnake.Num(); ++i)
	{
		wallsToSpawnAgainstSnake[i].RemoveSingle(wall);
	}

	wallsToSpawnBeginPlay.RemoveSingle(wall);
	wall->Destroy();

	worldSectors.Empty();

	DivideTheWorldIntoSectors();

	CheckingArrayForNull();
}

void AGroundBase::DestroyWalls()
{
	if (!(wallsToSpawnAgainstSnake.IsEmpty()))
	{
		for (int i = 0; i < wallsToSpawnAgainstSnake[0].Num();)
		{
			wallsToSpawnAgainstSnake[0][i]->Destroy();
			wallsToSpawnAgainstSnake[0].RemoveAt(i);
		}
	}

	CheckingArrayForNull();
}

bool AGroundBase::IsThereWallInFrontOfTheSnakeHead(const ASnakeBase* snake)
{
	EMovementDirection currentDirection = snake->GetLastMoveDir();
	float padding = snake->GetPadding();
	FVector currentPosition = snake->GetFullSnakeElements()[0]->GetActorLocation();
	

	switch (currentDirection)
	{
	case EMovementDirection::UP:
		currentPosition.X += padding;
		break;
	case EMovementDirection::DOWN:
		currentPosition.X -= padding;
		break;
	case EMovementDirection::LEFT:
		currentPosition.Y -= padding;
		break;
	case EMovementDirection::RIGHT:
		currentPosition.Y += padding;
		break;
	}

	for (int i = 0; i < wallsToSpawnBeginPlay.Num(); ++i)
	{
		if (currentPosition == wallsToSpawnBeginPlay[i]->GetActorLocation())
			return false;
	}

	return true;
}

bool AGroundBase::IsThereFoodOrSnakeElementOnTheSpawnWall(const ASnakeBase* snake, const FVector& currentLocationToSpawnWall)
{
	if (CheckPositionsSnakeElements(snake, currentLocationToSpawnWall))
		return false;

	if (CheckPositionsFoodOfTheWorld(currentLocationToSpawnWall))
		return false;

	return true;
}
