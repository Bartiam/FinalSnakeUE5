// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodBase.h"
#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFoodBase::AFoodBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Food"));
}

// Called when the game starts or when spawned
void AFoodBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFoodBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFoodBase::Interact(AActor* interactor, bool bIsHead)
{
	if (IsValid(interactor))
	{
		auto snake = Cast<ASnakeBase>(interactor);
		if (IsValid(snake))
		{
			snake->AddSnakeElements();
			ChangesPlaceOfFood(snake);
		}
	}
}

void AFoodBase::ChangesPlaceOfFood(const ASnakeBase* snake)
{
	if (!IsValid(snake))
		return;

	auto randomIndex = FMath::RandRange(0, snake->GetSizeOfSectors());
	auto snakeElements = snake->GetFullSnakeElements();
	auto currentPosition = snake->GetOneSector(randomIndex);

	for (int i = 0; i < snakeElements.Num(); ++i)
	{
		if (currentPosition == snakeElements[i]->GetActorLocation())
		{
			i = 0;
			randomIndex = FMath::RandRange(0, snake->GetSizeOfSectors());
			currentPosition = snake->GetOneSector(randomIndex);
		}
	}

	SetActorLocation(currentPosition);
}

