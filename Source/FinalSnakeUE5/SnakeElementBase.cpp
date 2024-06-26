// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeElementBase.h"
#include "Components/StaticMeshComponent.h"
#include "SnakeBase.h"

// Sets default values
ASnakeElementBase::ASnakeElementBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	meshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void ASnakeElementBase::SetSnakeOwner(ASnakeBase* owner)
{ this->snakeOwner = owner; }

void ASnakeElementBase::SetFirstElementMaterial_Implementation()
{
	meshComponent->OnComponentBeginOverlap.AddDynamic(this, &ASnakeElementBase::HandleBeginOverlap);
}

// Called when the game starts or when spawned
void ASnakeElementBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASnakeElementBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASnakeElementBase::HandleBeginOverlap(UPrimitiveComponent* OverlappedComp,
	AActor* other, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep,
	const FHitResult& sweepResult)
{
	if (IsValid(snakeOwner))
		snakeOwner->SnakeElementOverlap(this, other);
}

void ASnakeElementBase::Interact(AActor* interactor, bool bIsHead)
{
	if (IsValid(interactor))
	{
		auto snake = Cast<ASnakeBase>(interactor);
		if (IsValid(snake))
			snake->ThePlayerLost();
	}
}


void ASnakeElementBase::ToggleCollision()
{
	if (meshComponent->GetCollisionEnabled() == ECollisionEnabled::NoCollision)
		meshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	else if (meshComponent->GetCollisionEnabled() == ECollisionEnabled::QueryOnly)
		meshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
