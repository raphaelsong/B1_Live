// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "B1PlayerHUDWidget.generated.h"

struct FB1CharacterStat;

UCLASS()
class B1_API UB1PlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateStat(const FB1CharacterStat& BaseStat, const FB1CharacterStat& ModifierStat);
	void UpdateHp(float NewCurrentHp);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UB1HpBarWidget> WidgetHpBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UB1CharacterStatWidget> WidgetCharacterStat;
};
