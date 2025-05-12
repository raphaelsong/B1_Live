// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "B1AIController.generated.h"

/**
 * 
 */
UCLASS()
class B1_API AB1AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AB1AIController();

public:
	virtual void OnPossess(APawn* InPawn) override;

public:
	void RunAI();
	void StopAI();

protected:
	UPROPERTY(EditAnywhere, Category = AI)
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY(EditAnywhere, Category = AI)
	TObjectPtr<class UBehaviorTree> BTAsset;
};
