// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/B1PlayerController.h"


AB1PlayerController::AB1PlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void AB1PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AB1PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	
}

void AB1PlayerController::GameScoreChanged(int32 NewScore)
{
	K2_OnScoreChanged(NewScore);
}

void AB1PlayerController::GameClear()
{
	K2_GameClear();
}

void AB1PlayerController::GameOver()
{
	K2_GameOver();
}
