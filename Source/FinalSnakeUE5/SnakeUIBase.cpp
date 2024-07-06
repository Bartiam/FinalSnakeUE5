// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeUIBase.h"
#include "SnakeBase.h"
#include "Kismet/GameplayStatics.h"
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

FString USnakeUIBase::GetCurrentSkill()
{
	auto snake = Cast<ASnakeBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ASnakeBase::StaticClass()));

	if (!IsValid(snake))
		return FString("Nothing");

	auto currentSkill = snake->GetSkill();

	if (!IsValid(currentSkill))
		return FString("Nothing");

	FString currentNameOfSkill = snake->GetSkill()->GetName();

	return currentNameOfSkill;
}
