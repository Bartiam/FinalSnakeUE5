// Fill out your copyright notice in the Description page of Project Settings.


#include "WallBase.h"
#include "SnakeBase.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AWallBase::AWallBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall"));
	meshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

// Called when the game starts or when spawned
void AWallBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWallBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWallBase::Interact(AActor* interactor, bool bIsHead)
{
	if (IsValid(interactor))
	{
		auto snake = Cast<ASnakeBase>(interactor);
		if (IsValid(snake))
			snake->ThePlayerLost();
	}
}

