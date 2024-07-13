// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "Interactable.h"
#include "GroundBase.h"
#include "FoodBase.h"
#include "Kismet/GameplayStatics.h"
#include "SnakeGameModeBase.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	padding = 60.f;
	lastMoveDir = EMovementDirection::DOWN;
	currentStepIn = initialStepIn;
	bSnakeCanMove = true;
	initialSizeSnake = 4;
	scores = 0;
}

// Setters
void ASnakeBase::SetLastMoveDir(EMovementDirection moveDir)
{ this->lastMoveDir = moveDir; }

void ASnakeBase::SetSnakeCanMove(bool snakeCanMove)
{ this->bSnakeCanMove = snakeCanMove; }

void ASnakeBase::SetSkill(AFoodBase* newSkill)
{
	if (!IsValid(skill))
		skill = newSkill;
}

// Getters
EMovementDirection ASnakeBase::GetLastMoveDir() const
{ return lastMoveDir; }

bool ASnakeBase::GetSnakeCanMove() const 
{ return bSnakeCanMove; }

TArray<ASnakeElementBase*> ASnakeBase::GetFullSnakeElements() const
{ return snakeElements; }

const FVector ASnakeBase::GetSnakeElementLocation(int index)
{ return snakeElements[index]->GetActorLocation(); }

int32 ASnakeBase::GetNumbersOfSnakeElements()
{ return snakeElements.Num(); }

const float ASnakeBase::GetPadding() const
{ return padding; }

int32 ASnakeBase::GetScores() const
{ return scores; }

AFoodBase* ASnakeBase::GetSkill() const
{ return skill; }

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(currentStepIn);
	AddSnakeElements(initialSizeSnake);
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveSnake();
}

void ASnakeBase::AddSnakeElements(int count)
{
	for (int i = 0; i < count; ++i)
	{
		ASnakeElementBase* newSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(snakeELementClass, FTransform(RotationNewElement(), LocationNewElement()));
		newSnakeElem->SetActorHiddenInGame(true);
		newSnakeElem->SetSnakeOwner(this);
		int32 elemIndex = snakeElements.Add(newSnakeElem);
		if (elemIndex == 0)
		{
			newSnakeElem->SetFirstElementMesh();
			newSnakeElem->SetFirstElementMesh_Implementation();
		}
		if (IsValid(mainWorld))
			if (mainWorld->GetToggleCollisionWalls())
				newSnakeElem->SetSnakeMaterial();
	}

	SetSnakeElementsAssets();

	TimeToStarveToDeath();

	scores += count;
}

void ASnakeBase::StepBack()
{
	snakeElements[0]->ToggleCollision();
	for (int i = 0; i <= snakeElements.Num() - 3; i++) 
	{
		auto currentElem = snakeElements[i];
		auto nextElem = snakeElements[i + 2];
		currentElem->SetActorLocation(nextElem->GetActorLocation());
		currentElem->SetActorRotation(nextElem->GetActorRotation());
	}
	snakeElements[snakeElements.Num() - 1]->SetActorLocation(previousLastPosition);
	snakeElements[snakeElements.Num() - 2]->SetActorLocation(lastPosition);

	snakeElements[snakeElements.Num() - 1]->SetActorRotation(previousElemRotation);
	snakeElements[snakeElements.Num() - 2]->SetActorRotation(lastElemRotation);

	snakeElements[0]->ToggleCollision();
}

void ASnakeBase::teleportSnake()
{
	FVector currentLocationOfPrevHead = snakeElements[1]->GetActorLocation();
	snakeElements[0]->SetActorLocation(FVector(currentLocationOfPrevHead.X * (-1), currentLocationOfPrevHead.Y * (-1), currentLocationOfPrevHead.Z));
}

void ASnakeBase::SlowDownSnake(const float& howManySeconds, const float& speedChange)
{
	GetWorldTimerManager().ClearTimer(timerSlowDownSnake);

	if ((currentStepIn + speedChange) >= minSpeedStepIn)
		currentStepIn = minSpeedStepIn;
	else
		currentStepIn += speedChange;

	SetActorTickInterval(currentStepIn);

	GetWorld()->GetTimerManager().SetTimer(timerSlowDownSnake, this, &ASnakeBase::CancellationBonus, howManySeconds, false);
}

void ASnakeBase::SpeedUpSnake(const float& howManySeconds, const float& speedChange)
{
	GetWorldTimerManager().ClearTimer(timerSpeedUpSnake);

	if ((currentStepIn - speedChange) <= maxSpeedStepIn)
		currentStepIn = maxSpeedStepIn;
	else
		currentStepIn -= speedChange;

	SetActorTickInterval(currentStepIn);

	GetWorld()->GetTimerManager().SetTimer(timerSpeedUpSnake, this, &ASnakeBase::CancellationBonus, howManySeconds, false);
}

void ASnakeBase::CancellationBonus()
{
	currentStepIn = initialStepIn;

	SetActorTickInterval(currentStepIn);
}

void ASnakeBase::MoveSnake()
{
	bSnakeCanMove = true;

	FVector movementVector(ForceInitToZero);

	switch (lastMoveDir)
	{
	case EMovementDirection::UP:
		movementVector.X += padding;
		snakeElements[0]->SetActorRotation(FRotator(0.f, 270.f, 0.f));
		break;
	case EMovementDirection::DOWN:
		movementVector.X -= padding;
		snakeElements[0]->SetActorRotation(FRotator(0.f, 90.f, 0.f));
		break;
	case EMovementDirection::LEFT:
		movementVector.Y -= padding;
		snakeElements[0]->SetActorRotation(FRotator(0.f, 180.f, 0.f));
		break;
	case EMovementDirection::RIGHT:
		movementVector.Y += padding;
		snakeElements[0]->SetActorRotation(FRotator(0.f, 0.f, 0.f));
		break;
	}

	snakeElements[0]->ToggleCollision();
	previousLastPosition = lastPosition;
	lastPosition = snakeElements[snakeElements.Num() - 1]->GetActorLocation();

	previousElemRotation = lastElemRotation;
	lastElemRotation = snakeElements[snakeElements.Num() - 1]->GetActorRotation();

	for (int i = snakeElements.Num() - 1; i > 0; --i)
	{
		auto currentELem = snakeElements[i];
		auto prevElem = snakeElements[i - 1];
		currentELem->SetActorLocation(prevElem->GetActorLocation());
		currentELem->SetActorRotation(prevElem->GetActorRotation());
		currentELem->SetActorHiddenInGame(false);
	}

	snakeElements[0]->AddActorWorldOffset(movementVector);
	snakeElements[0]->SetActorHiddenInGame(false);
	snakeElements[0]->ToggleCollision();
}

void ASnakeBase::SetSnakeElementsAssets()
{
	for (int i = 1; i < snakeElements.Num(); ++i)
		snakeElements[i]->SetElementsMesh();

	snakeElements[snakeElements.Num() - 1]->SetLastElementMesh();
}

FRotator ASnakeBase::RotationNewElement()
{
	FRotator result;

	if (GetNumbersOfSnakeElements() == 0)
		result = FRotator(0.f, 90.f, 0.f);
	else
		result = snakeElements[snakeElements.Num() - 1]->GetActorRotation();

	return result;
}

FVector ASnakeBase::LocationNewElement()
{
	FVector result;
	FVector locationLastElement;
	FVector penultimateElement;

	if (GetNumbersOfSnakeElements() == 0)
	{
		result = FVector(GetNumbersOfSnakeElements() * padding + 30.f, 30.f, 30.f);
	}
	else
	{
		locationLastElement = snakeElements[GetNumbersOfSnakeElements() - 1]->GetActorLocation();
		if (GetNumbersOfSnakeElements() == 1)
		{
			switch (lastMoveDir)
			{
			case EMovementDirection::UP:
				result = FVector(locationLastElement.X - padding, locationLastElement.Y, locationLastElement.Z);
				break;
			case EMovementDirection::DOWN:
				result = FVector(locationLastElement.X + padding, locationLastElement.Y, locationLastElement.Z);
				break;
			case EMovementDirection::LEFT:
				result = FVector(locationLastElement.X, locationLastElement.Y - padding, locationLastElement.Z);
				break;
			case EMovementDirection::RIGHT:
				result = FVector(locationLastElement.X, locationLastElement.Y + padding, locationLastElement.Z);
				break;
			}
		}
		else
		{
			penultimateElement = snakeElements[GetNumbersOfSnakeElements() - 2]->GetActorLocation();
			result = LocationNewElementMoreOne(locationLastElement, penultimateElement);
		}
	}

	return result;
}

FVector ASnakeBase::LocationNewElementMoreOne(const FVector& locationLastElement, const FVector& penultimateElement)
{
	FVector result;
	if (penultimateElement.X > locationLastElement.X)
		result = FVector(locationLastElement.X - padding, locationLastElement.Y, locationLastElement.Z);
	else if (penultimateElement.X < locationLastElement.X)
		result = FVector(locationLastElement.X + padding, locationLastElement.Y, locationLastElement.Z);
	else if (penultimateElement.Y > locationLastElement.Y)
		result = FVector(locationLastElement.X, locationLastElement.Y - padding, locationLastElement.Z);
	else if (penultimateElement.Y < locationLastElement.Y)
		result = FVector(locationLastElement.X, locationLastElement.Y + padding, locationLastElement.Z);

	return result;
}

void ASnakeBase::TimeToStarveToDeath()
{
	GetWorldTimerManager().ClearTimer(timerForDead);

	GetWorldTimerManager().SetTimer(timerForDead, this, &ASnakeBase::ThePlayerLost, 30.f);
}

void ASnakeBase::SnakeElementOverlap(ASnakeElementBase* overlappedComp, AActor* other)
{
	if (IsValid(overlappedComp))
	{
		int32 indexElem;
		snakeElements.Find(overlappedComp, indexElem);
		bool bIsHead = indexElem == 0;
		IInteractable* interactableInterface = Cast<IInteractable>(other);
		if (interactableInterface)
		{
			interactableInterface->Interact(this, bIsHead);
		}
	}
}

void ASnakeBase::ThePlayerLost()
{
	for (int i = 0; i < snakeElements.Num();)
	{
		snakeElements[i]->Destroy();
		snakeElements.RemoveAt(i);
	}

	Destroy();

	auto gameMode = Cast<ASnakeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	gameMode->GameOver();
}

void ASnakeBase::DeleteSnakeElement()
{
	snakeElements[snakeElements.Num() - 1]->Destroy();
	snakeElements.RemoveAt(snakeElements.Num() - 1);
	TimeToStarveToDeath();
	scores--;

	SetSnakeElementsAssets();

	if (snakeElements.Num() <= 1)
		ThePlayerLost();
}
