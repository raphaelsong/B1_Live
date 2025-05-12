// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/B1ItemData.h"
#include "B1PotionItemData.generated.h"

/**
 * 
 */
UCLASS()
class B1_API UB1PotionItemData : public UB1ItemData
{
	GENERATED_BODY()
	
public:
	UB1PotionItemData();

public:
	UPROPERTY(EditAnywhere, Category = Hp)
	float HealAmount;
};
