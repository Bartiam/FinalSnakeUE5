// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakePawnBase.h"
#include "Kismet/GameplayStatics.h"
#include "FoodBase.h"

#include "SnakeElementBase.h"

#include "BonusFoodAccelerationBase.h"
#include "BonusFoodDecelerationBase.h"
#include "BonusFoodPassageThroughWalls.h"

// Sets default values
ASnakePawnBase::ASnakePawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Snake Camera"));
	RootComponent = mainCamera;
	bIsGameOver = false;
}

// Called when the game starts or when spawned
void ASnakePawnBase::BeginPlay()
{
	Super::BeginPlay();
	mainCamera->SetWorldRotation(FRotator(-90.f, 0.f, 0.f));
	CreateSnakeActor();
}

// Called every frame
void ASnakePawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASnakePawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Vertical", this, &ASnakePawnBase::HandleVerticalInput);
	PlayerInputComponent->BindAxis("Horizontal", this, &ASnakePawnBase::HandleHorizontalInput);

	PlayerInputComponent->BindAction("UseSkill", EInputEvent::IE_Pressed, this, &ASnakePawnBase::UseCurrentSkill);
}

void ASnakePawnBase::CreateSnakeActor()
{
	snakeActor = GetWorld()->SpawnActor<ASnakeBase>(snakeActorClass, FTransform());
}

void ASnakePawnBase::HandleVerticalInput(float value)
{
	if (IsValid(snakeActor)) {
		if (value < 0.f && snakeActor->GetLastMoveDir() != EMovementDirection::UP && snakeActor->GetSnakeCanMove())
		{
			snakeActor->SetLastMoveDir(EMovementDirection::DOWN);
			snakeActor->SetSnakeCanMove(false);
		}
		else if (value > 0.f && snakeActor->GetLastMoveDir() != EMovementDirection::DOWN && snakeActor->GetSnakeCanMove())
		{
			snakeActor->SetLastMoveDir(EMovementDirection::UP);
			snakeActor->SetSnakeCanMove(false);
		}
	}
}

void ASnakePawnBase::HandleHorizontalInput(float value)
{
	if (IsValid(snakeActor)) {
		if (value < 0.f && snakeActor->GetLastMoveDir() != EMovementDirection::RIGHT && snakeActor->GetSnakeCanMove())
		{
			snakeActor->SetLastMoveDir(EMovementDirection::LEFT);
			snakeActor->SetSnakeCanMove(false);
		}
		else if (value > 0.f && snakeActor->GetLastMoveDir() != EMovementDirection::LEFT && snakeActor->GetSnakeCanMove())
		{
			snakeActor->SetLastMoveDir(EMovementDirection::RIGHT);
			snakeActor->SetSnakeCanMove(false);
		}
	}
}

void ASnakePawnBase::UseCurrentSkill()
{
	auto currentSkill = snakeActor->GetSkill();

	if (IsValid(currentSkill))
	{
		auto snakeElements = snakeActor->GetFullSnakeElements();

		currentSkill->SetActorLocation(snakeElements[0]->GetActorLocation());
	}
}

