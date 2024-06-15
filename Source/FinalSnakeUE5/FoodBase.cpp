// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodBase.h"
#include "SnakeBase.h"
#include "Components/StaticMeshComponent.h"
#include "GroundBase.h"

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
			groundOwner->SpawnFood();

			float checkChanceForSpawnWallsAgainsSnake = FMath::RandRange(0.f, 1.f);

			if (checkChanceForSpawnWallsAgainsSnake >= 0.3f)
				groundOwner->SpawnWallsAgainstSnake(snake);
		}
	}
}
