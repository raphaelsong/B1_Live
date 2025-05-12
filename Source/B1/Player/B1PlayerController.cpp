// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/B1PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameData/B1SaveGame.h"


AB1PlayerController::AB1PlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void AB1PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode); 

	SaveGameInstance = Cast<UB1SaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Player0"), 0));
	if (SaveGameInstance == nullptr)
	{
		SaveGameInstance = NewObject<UB1SaveGame>();
		SaveGameInstance->RetryCount = 0;
	}
	else
	{
		SaveGameInstance->RetryCount++;
	}

	K2_GameRetryCount(SaveGameInstance->RetryCount);
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

	if (SaveGameInstance)
	{
		SaveGameInstance->RetryCount = 0;
		if (!UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("Player0"), 0))
		{
			UE_LOG(LogTemp, Error, TEXT("SaveGame Error!"));
		}
	}
}

void AB1PlayerController::GameOver()
{
	K2_GameOver();

	if (SaveGameInstance)
	{
		if (!UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("Player0"), 0))
		{
			UE_LOG(LogTemp, Error, TEXT("SaveGame Error!"));
		}
	}

	K2_GameRetryCount(SaveGameInstance->RetryCount);
}
