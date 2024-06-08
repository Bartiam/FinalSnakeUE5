// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "Interactable.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	padding = 60.f;
	lastMoveDir = EMovementDirection::DOWN;
	stepIn = 0.4f;
	bSnakeCanMove = true;
	initialSizeSnake = 4;
}

// Setters
void ASnakeBase::SetLastMoveDir(EMovementDirection moveDir)
{ this->lastMoveDir = moveDir; }

void ASnakeBase::SetSnakeCanMove(bool snakeCanMove)
{ this->bSnakeCanMove = snakeCanMove; }

void ASnakeBase::DeleteSnakeElement()
{
	snakeElements[snakeElements.Num() - 1]->Destroy();
	snakeElements.RemoveAt(snakeElements.Num() - 1);
}

// Getters
EMovementDirection ASnakeBase::GetLastMoveDir() const
{ return lastMoveDir; }

bool ASnakeBase::GetSnakeCanMove() const 
{ return bSnakeCanMove; }

const TArray<ASnakeElementBase*> ASnakeBase::GetFullSnakeElements() const
{ return snakeElements; }

const FVector ASnakeBase::GetSnakeElementLocation(int index)
{ return snakeElements[index]->GetActorLocation(); }

const int32 ASnakeBase::GetNumbersOfSnakeElements()
{ return snakeElements.Num(); }

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	AddSnakeElements(initialSizeSnake);
	SetActorTickInterval(stepIn);
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
		FVector newLocation(snakeElements.Num() * padding + 30, 30, 20.f);
		ASnakeElementBase* newSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(snakeELementClass, FTransform(newLocation));
		newSnakeElem->SetActorHiddenInGame(true);
		newSnakeElem->SetSnakeOwner(this);
		int32 elemIndex = snakeElements.Add(newSnakeElem);
		if (elemIndex == 0)
		{
			newSnakeElem->SetFirstElementMaterial();
			newSnakeElem->SetFirstElementMaterial_Implementation();
		}
	}
}

void ASnakeBase::StepBack()
{
	snakeElements[0]->ToggleCollision();
	for (int i = 0; i <= snakeElements.Num() - 3; i++) 
	{
		auto currentElem = snakeElements[i];
		auto nextElem = snakeElements[i + 2];
		currentElem->SetActorLocation(nextElem->GetActorLocation());
	}
	snakeElements[snakeElements.Num() - 1]->SetActorLocation(previousLastPosition);
	snakeElements[snakeElements.Num() - 2]->SetActorLocation(lastPosition);
	snakeElements[0]->ToggleCollision();
}

void ASnakeBase::teleportSnake()
{

}

void ASnakeBase::MoveSnake()
{
	bSnakeCanMove = true;

	FVector movementVector(ForceInitToZero);

	switch (lastMoveDir)
	{
	case EMovementDirection::UP:
		movementVector.X += padding;
		break;
	case EMovementDirection::DOWN:
		movementVector.X -= padding;
		break;
	case EMovementDirection::LEFT:
		movementVector.Y += padding;
		break;
	case EMovementDirection::RIGHT:
		movementVector.Y -= padding;
		break;
	}

	snakeElements[0]->ToggleCollision();
	previousLastPosition = lastPosition;
	lastPosition = snakeElements[snakeElements.Num() - 1]->GetActorLocation();


	for (int i = snakeElements.Num() - 1; i > 0; --i)
	{
		auto currentELem = snakeElements[i];
		auto prevElem = snakeElements[i - 1];
		currentELem->SetActorLocation(prevElem->GetActorLocation());
		currentELem->SetActorHiddenInGame(false);
	}

	snakeElements[0]->AddActorWorldOffset(movementVector);
	snakeElements[0]->SetActorHiddenInGame(false);
	snakeElements[0]->ToggleCollision();
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

void ASnakeBase::DestroyFullSnakeElements()
{
	for (int i = 0; i < snakeElements.Num();)
	{
		snakeElements[i]->Destroy();
		snakeElements.RemoveAt(i);
	}
	Destroy();
}

