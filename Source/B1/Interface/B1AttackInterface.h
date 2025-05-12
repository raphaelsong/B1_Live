// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "B1AttackInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UB1AttackInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class B1_API IB1AttackInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void AttackHitCheck() = 0;
};
