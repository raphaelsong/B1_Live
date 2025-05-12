// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/B1PlayerHUDWidget.h"
#include "B1HpBarWidget.h"
#include "B1CharacterStatWidget.h"

void UB1PlayerHUDWidget::UpdateStat(const FB1CharacterStat& BaseStat, const FB1CharacterStat& ModifierStat)
{
	WidgetHpBar->UpdateStat(BaseStat, ModifierStat);
	WidgetCharacterStat->UpdateStat(BaseStat, ModifierStat);
}

void UB1PlayerHUDWidget::UpdateHp(float NewCurrentHp)
{
	WidgetHpBar->UpdateHp(NewCurrentHp);
}
