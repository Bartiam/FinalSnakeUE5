// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakePawnBase.h"

// Sets default values
ASnakePawnBase::ASnakePawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Snake Camera"));
	RootComponent = mainCamera;
}

// Called when the game starts or when spawned
void ASnakePawnBase::BeginPlay()
{
	Super::BeginPlay();
	mainCamera->SetWorldRotation(FRotator(-90, 0, 0));
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

}

void ASnakePawnBase::CreateSnakeActor()
{
	snakeActor = GetWorld()->SpawnActor<ASnakeBase>(snakeActorClass, FTransform());
}

void ASnakePawnBase::HandleVerticalInput(float value)
{
	if (IsValid(snakeActor)) {
		if (value < 0.f && snakeActor->GetLastMoveDir() != EMovementDirection::UP)
			snakeActor->SetLastMoveDir(EMovementDirection::DOWN);
		else if (value > 0.f && snakeActor->GetLastMoveDir() != EMovementDirection::DOWN)
			snakeActor->SetLastMoveDir(EMovementDirection::UP);
	}
}

void ASnakePawnBase::HandleHorizontalInput(float value)
{
	if (IsValid(snakeActor)) {
		if (value < 0.f && snakeActor->GetLastMoveDir() != EMovementDirection::RIGHT)
			snakeActor->SetLastMoveDir(EMovementDirection::LEFT);
		else if (value > 0.f && snakeActor->GetLastMoveDir() != EMovementDirection::LEFT)
			snakeActor->SetLastMoveDir(EMovementDirection::RIGHT);
	}
}

