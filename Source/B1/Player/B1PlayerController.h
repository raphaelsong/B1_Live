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

};
