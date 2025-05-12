// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "B1GameSingleton.generated.h"

struct FB1CharacterStat;

/**
 * 
 */
UCLASS()
class B1_API UB1GameSingleton : public UObject
{
	GENERATED_BODY()
	
public:
	UB1GameSingleton();
	static UB1GameSingleton& Get();

public:
	FB1CharacterStat GetCharacterStat(int32 InLevel) const;
	FORCEINLINE int32 GetCharacterMaxLevel() { return CharacterMaxLevel; }

private:
	TArray<FB1CharacterStat> CharacterStatTable;

	int32 CharacterMaxLevel;
};
