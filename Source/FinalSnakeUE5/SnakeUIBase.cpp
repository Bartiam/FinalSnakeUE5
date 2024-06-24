// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeUIBase.h"
#include "SnakeBase.h"
#include "Kismet/GameplayStatics.h"

float USnakeUIBase::GetCurrentTimeToDead()
{
	auto snake = Cast<ASnakeBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ASnakeBase::StaticClass()));

	

	return GetWorld()->GetTimerManager().GetTimerElapsed(snake->timerForDead) / 100.f;
}
