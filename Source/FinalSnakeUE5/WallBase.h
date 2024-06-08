// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"

#include "WallBase.generated.h"

class UStaticMeshComponent;

UCLASS()
class FINALSNAKEUE5_API AWallBase : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWallBase();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Wall")
	UStaticMeshComponent* meshComponent;

	UPROPERTY(BlueprintReadWrite)
	class AGroundBase* groundOwner;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* interactor, bool bIsHead) override;

};
