// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interface/B1GameInterface.h"
#include "B1GameMode.generated.h"

/**
 * 
 */
UCLASS()
class B1_API AB1GameMode : public AGameModeBase, public IB1GameInterface
{
	GENERATED_BODY()
	
public:
	AB1GameMode();

public:
	// Inherited via IB1GameInterface
	virtual void OnPlayerScoreChanged(int32 NewPlayerScore) override;
	virtual void AddPlyerScore(int32 AddPlayerScore) override;
	virtual void OnPlayerDead() override;
	virtual bool IsGameCleared() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ClearScore;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CurrentScore;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 bIsCleared : 1;


};
