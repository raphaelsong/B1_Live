// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/B1ItemData.h"
#include "GameData/B1CharacterStat.h"
#include "B1WeaponItemData.generated.h"

/**
 * 
 */
UCLASS()
class B1_API UB1WeaponItemData : public UB1ItemData
{
	GENERATED_BODY()

public:
	UB1WeaponItemData();

public:
	UPROPERTY(EditAnywhere, Category = Mesh)
	TSoftObjectPtr<class USkeletalMesh> WeaponMesh;

	UPROPERTY(EditAnywhere, Category = Stat)
	FB1CharacterStat ModifierStat;
};
