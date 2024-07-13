// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodBase.h"
#include "SnakeBase.h"
#include "Components/StaticMeshComponent.h"
#include "GroundBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFoodBase::AFoodBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Food"));
	bIsSwitchHiddenInGame = true;
}

FString AFoodBase::GetNameOfSkill()
{return FString();}

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
			snake->AddSnakeElements(2);
			groundOwner->SpawnFood(snake);

			float checkChanceForSpawnWallsAgainsSnake = FMath::RandRange(0.f, 1.f);

			if (checkChanceForSpawnWallsAgainsSnake >= 0.3f)
				groundOwner->SpawnWallsAgainstSnake(snake);

			checkChanceForSpawnWallsAgainsSnake = FMath::RandRange(0.f, 1.f);

			if (checkChanceForSpawnWallsAgainsSnake >= 0.5f)
			{
				checkChanceForSpawnWallsAgainsSnake = FMath::RandRange(0.f, 1.f);
				if (checkChanceForSpawnWallsAgainsSnake >= 0.5f)
					groundOwner->BonusFoodSpawn(snake, (int)(EFoodsEnum::BonusFoodAcceliration));
				else 
					groundOwner->BonusFoodSpawn(snake, (int)(EFoodsEnum::BonusFoodDeceleration));
			}
		}
	}
}

void AFoodBase::SetTimerForCurrentFood()
{
	FTimerHandle TimerBeforeFoodDestroyed;
	FTimerHandle TimerToStartTheFlashingTimer;
	GetWorldTimerManager().SetTimer(TimerBeforeFoodDestroyed, this, &AFoodBase::IntermediateFunction, 15.f);
	GetWorldTimerManager().SetTimer(TimerToStartTheFlashingTimer, this, &AFoodBase::SettingTimerToDisplayFoodInTheWorld, 10.f);
}

void AFoodBase::IntermediateFunction()
{
	auto snake = Cast<ASnakeBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ASnakeBase::StaticClass()));
	if (IsValid(snake))
	{
		auto currentSkill = snake->GetSkill();
		if (IsValid(currentSkill))
		{
			if (currentSkill != this)
				groundOwner->DestroyFoodInTheWorld(this);
		}
		else
			groundOwner->DestroyFoodInTheWorld(this);
	}
}

void AFoodBase::FlashingFoodInTheGame()
{
	SetActorHiddenInGame(bIsSwitchHiddenInGame);
	if (bIsSwitchHiddenInGame)
		bIsSwitchHiddenInGame = false;
	else
		bIsSwitchHiddenInGame = true;
}

void AFoodBase::SettingTimerToDisplayFoodInTheWorld()
{
	FTimerHandle TimerToStartFlashing;
	GetWorldTimerManager().SetTimer(TimerToStartFlashing, this, &AFoodBase::FlashingFoodInTheGame, 0.1f, true);
}
