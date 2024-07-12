// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeUIBase.h"
#include "SnakeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"
#include "FoodBase.h"

float USnakeUIBase::GetCurrentTimeToDead()
{
	auto snake = Cast<ASnakeBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ASnakeBase::StaticClass()));

	if (!IsValid(snake))
		return 0.f;

	return GetWorld()->GetTimerManager().GetTimerElapsed(snake->timerForDead) / 30.f;
}

FString USnakeUIBase::GetCurrentScores()
{
	auto snake = Cast<ASnakeBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ASnakeBase::StaticClass()));

	if (!IsValid(snake))
		return FString();

	FString currentScores = "Score: ";
	
	currentScores.AppendInt(snake->GetScores());

	return currentScores;
}

UTexture* USnakeUIBase::GetIcon()
{
	auto snake = Cast<ASnakeBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ASnakeBase::StaticClass()));

	if (!IsValid(snake))
		return nullptr;

	if (!IsValid(snake->GetSkill()))
		return snake->defaultIcon;

	return snake->GetSkill()->icon;
}

FString USnakeUIBase::GetNameOfSkill()
{
	auto snake = Cast<ASnakeBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ASnakeBase::StaticClass()));

	if (!IsValid(snake) || !IsValid(snake->GetSkill()))
		return FString(TEXT("Nothing"));

	return snake->GetSkill()->GetNameOfSkill();
}
