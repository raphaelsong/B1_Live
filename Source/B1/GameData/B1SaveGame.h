// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "B1SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class B1_API UB1SaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UB1SaveGame();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RetryCount;
};
