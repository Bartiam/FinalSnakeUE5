// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	padding = 60.f;
	stepIn = 0.4f;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	CreateSnakeElements(4);
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASnakeBase::CreateSnakeElements(int count)
{
	for (int i = 0; i < count; ++i)
	{
		FVector location(snakeElements.Num() * padding, 0, 40);
		auto newSnakeElement = GetWorld()->SpawnActor<ASnakeElementBase>(snakeELementClass, FTransform(location));
		snakeElements.Add(newSnakeElement);
	}
}

