// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakePawnBase.h"

// Sets default values
ASnakePawnBase::ASnakePawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Snake Camera"));
	RootComponent = mainCamera;
	mainCamera->SetWorldRotation(FRotator(-90, 0, 0));
}

// Called when the game starts or when spawned
void ASnakePawnBase::BeginPlay()
{
	Super::BeginPlay();
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

}

void ASnakePawnBase::CreateSnakeActor()
{
	snakeActor = GetWorld()->SpawnActor<ASnakeBase>(snakeActorClass, FTransform());
}

