// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "B1HpBarWidget.generated.h"

struct FB1CharacterStat;

UCLASS()
class B1_API UB1HpBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UB1HpBarWidget(const FObjectInitializer& ObjectInitializer);

public:
	void UpdateStat(const FB1CharacterStat& BaseStat, const FB1CharacterStat& ModifierStat);
	void UpdateHp(float NewCurrentHp);

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UProgressBar> HpBar;

	float CurrentHp;
	float MaxHp;
};
