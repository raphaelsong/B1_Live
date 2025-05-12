// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/B1ItemData.h"
#include "GameData/B1CharacterStat.h"
#include "B1ScrollItemData.generated.h"

/**
 * 
 */
UCLASS()
class B1_API UB1ScrollItemData : public UB1ItemData
{
	GENERATED_BODY()
	
public:
	UB1ScrollItemData();

public:
	UPROPERTY(EditAnywhere, Category = Stat)
	FB1CharacterStat BaseStat;
};
