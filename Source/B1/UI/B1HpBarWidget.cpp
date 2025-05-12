// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/B1HpBarWidget.h"
#include "GameData/B1CharacterStat.h"
#include "Components/ProgressBar.h"

UB1HpBarWidget::UB1HpBarWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	MaxHp = -1.f;
}

void UB1HpBarWidget::UpdateStat(const FB1CharacterStat& BaseStat, const FB1CharacterStat& ModifierStat)
{
	MaxHp = (BaseStat + ModifierStat).MaxHp;

	if (HpBar)
	{
		HpBar->SetPercent(CurrentHp / MaxHp);
	}
}

void UB1HpBarWidget::UpdateHp(float NewCurrentHp)
{
	CurrentHp = NewCurrentHp;

	if (HpBar)
	{
		HpBar->SetPercent(CurrentHp / MaxHp);
	}
}
