// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"

#include "SnakeElementBase.generated.h"

class UStaticMeshComponent;
class ASnakeBase;

UCLASS()
class FINALSNAKEUE5_API ASnakeElementBase : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeElementBase();

	// Setters
	void SetSnakeOwner(ASnakeBase* owner);

	UFUNCTION(BlueprintNativeEvent)
	void SetFirstElementMesh();
	void SetFirstElementMesh_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void SetElementsMesh();
	void SetElementsMesh_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void SetLastElementMesh();
	void SetLastElementMesh_Implementation();

	void ToggleCollision();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* meshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Declaring private variables

	ASnakeBase* snakeOwner;

	UFUNCTION()
	void HandleBeginOverlap(UPrimitiveComponent* OverlappedComp,
		AActor* other, UPrimitiveComponent* otherComp,
		int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	virtual void Interact(AActor* interactor, bool bIsHead) override;
};
