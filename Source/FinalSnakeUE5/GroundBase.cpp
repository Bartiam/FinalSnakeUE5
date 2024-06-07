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
	food = GetWorld()->SpawnActor<AFoodBase>(foodClass, FTransform(worldSectors[50]));
	food->SetGroundOwner(this);
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
			worldSectors.Add(FVector(i, j, 20.f));
		}
	}
}

void AGroundBase::SpawnFood(const ASnakeBase* snake)
{
	auto randomIndex = FMath::RandRange(0, GetSizeOfSectors());
	auto snakeElements = snake->GetFullSnakeElements();
	auto currentPosition = GetOneSector(randomIndex);

	for (int i = 0; i < snakeElements.Num(); ++i)
	{
		if (currentPosition == snakeElements[i]->GetActorLocation())
		{
			i = 0;
			randomIndex = FMath::RandRange(0, GetSizeOfSectors());
			currentPosition = GetOneSector(randomIndex);
		}
	}

	food->SetActorLocation(currentPosition);
}

