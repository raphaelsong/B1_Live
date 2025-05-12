// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "B1PlayerController.generated.h"


/**
 * 
 */
UCLASS()
class B1_API AB1PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AB1PlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:
	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "OnScoreChangedCpp"))
	void K2_OnScoreChanged(int32 NewScore);
	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "OnGameClearCpp"))
	void K2_GameClear();
	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "OnGameOverCpp"))
	void K2_GameOver();
	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "OnGameRetryCount"))
	void K2_GameRetryCount(int32 NewRetryCount);

public:
	void GameScoreChanged(int32 NewScore);
	void GameClear();
	void GameOver();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = SaveGame)
	TObjectPtr<class UB1SaveGame> SaveGameInstance;
};
