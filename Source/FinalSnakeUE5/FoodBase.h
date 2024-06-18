// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"

#include "FoodBase.generated.h"

class UStaticMeshComponent;
class AGroundBase;

UENUM()
enum class EFoodsEnum
{
	SimpleFood = 1,
	BadFood,
	BonusFoodFromTheSoftWall,
	BonusFoodAcceliration,
	BonusFoodDeceleration
};

UCLASS()
class FINALSNAKEUE5_API AFoodBase : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFoodBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Food")
	UStaticMeshComponent* meshComponent;

	UPROPERTY(BlueprintReadWrite)
	AGroundBase* groundOwner;

	const float secondsBonusValidity = 10.f;
	const float speedChangesOn = 0.05f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact(AActor* interactor, bool bIsHead) override;

	
};
