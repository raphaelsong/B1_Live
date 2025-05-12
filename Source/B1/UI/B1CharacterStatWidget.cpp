// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/B1CharacterStatWidget.h"
#include "GameData/B1CharacterStat.h"
#include "Components/TextBlock.h"

void UB1CharacterStatWidget::UpdateStat(const FB1CharacterStat& BaseStat, const FB1CharacterStat& ModifierStat)
{
	MaxHpBase->SetText(FText::FromString(FString::SanitizeFloat(BaseStat.MaxHp)));
	AttackBase->SetText(FText::FromString(FString::SanitizeFloat(BaseStat.Attack)));
	AttackRangeBase->SetText(FText::FromString(FString::SanitizeFloat(BaseStat.AttackRange)));
	AttackRadiusBase->SetText(FText::FromString(FString::SanitizeFloat(BaseStat.AttackRadius)));
	AttackSpeedBase->SetText(FText::FromString(FString::SanitizeFloat(BaseStat.AttackSpeed)));
	MovementSpeedBase->SetText(FText::FromString(FString::SanitizeFloat(BaseStat.MovementSpeed)));

	MaxHpModifier->SetText(FText::FromString(FString::SanitizeFloat(ModifierStat.MaxHp)));
	AttackModifier->SetText(FText::FromString(FString::SanitizeFloat(ModifierStat.Attack)));
	AttackRangeModifier->SetText(FText::FromString(FString::SanitizeFloat(ModifierStat.AttackRange)));
	AttackRadiusModifier->SetText(FText::FromString(FString::SanitizeFloat(ModifierStat.AttackRadius)));
	AttackSpeedModifier->SetText(FText::FromString(FString::SanitizeFloat(ModifierStat.AttackSpeed)));
	MovementSpeedModifier->SetText(FText::FromString(FString::SanitizeFloat(ModifierStat.MovementSpeed)));
}
