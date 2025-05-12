// Fill out your copyright notice in the Description page of Project Settings.


#include "GameData/B1CharacterStatComponent.h"
#include "GameData/B1GameSingleton.h"

UB1CharacterStatComponent::UB1CharacterStatComponent()
{
	bWantsInitializeComponent = true;
	CurrentLevel = 1.0f;

}

void UB1CharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UB1CharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetupLevel(CurrentLevel);
	SetHp(BaseStat.MaxHp);
}

void UB1CharacterStatComponent::SetupLevel(int32 NewLevel)
{
	CurrentLevel = FMath::Clamp(NewLevel, 1, UB1GameSingleton::Get().GetCharacterMaxLevel());
	SetBaseStat(UB1GameSingleton::Get().GetCharacterStat(CurrentLevel));
}

float UB1CharacterStatComponent::ApplyDamage(float InDamage)
{
	const float PreHp = CurrentHp;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0.0f, InDamage);

	SetHp(PreHp - ActualDamage);
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}
	return ActualDamage;
}
