// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameData/B1CharacterStat.h"
#include "B1CharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float /*CurrentHp*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStatChangedDelegate, const FB1CharacterStat& /*BaseStat*/, const FB1CharacterStat& /*ModifierStat*/);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class B1_API UB1CharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UB1CharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:
	void SetupLevel(int32 NewLevel);
	float ApplyDamage(float InDamage);

public:
	FORCEINLINE float GetCurrentLevel() { return CurrentLevel; }
	FORCEINLINE float GetCurrentHp() { return CurrentHp; }
	FORCEINLINE const FB1CharacterStat& GetBaseStat() { return BaseStat; }
	FORCEINLINE const FB1CharacterStat& GetModifierStat() { return ModifierStat; }
	FORCEINLINE FB1CharacterStat GetTotalStat() { return BaseStat + ModifierStat; }

public:
	FORCEINLINE void SetHp(float NewHp)
	{
		CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, GetTotalStat().MaxHp);
		OnHpChanged.Broadcast(CurrentHp);
	}

	FORCEINLINE void AddHp(float InHp)
	{
		CurrentHp = FMath::Clamp<float>(CurrentHp + InHp, 0.0f, GetTotalStat().MaxHp);
		OnHpChanged.Broadcast(CurrentHp);
	}

	FORCEINLINE void SetBaseStat(const FB1CharacterStat& InBaseStat)
	{
		BaseStat = InBaseStat;
		OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat());
	}

	FORCEINLINE void SetModifierStat(const FB1CharacterStat& InModiferStat)
	{
		ModifierStat = InModiferStat;
		OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat());
	}

	FORCEINLINE void AddBaseStat(const FB1CharacterStat& InAddBaseStat)
	{
		BaseStat = BaseStat + InAddBaseStat;
		OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat());
	}

	FORCEINLINE void AddModifierStat(const FB1CharacterStat& InAddModifierStat)
	{
		ModifierStat = ModifierStat + InAddModifierStat;
		OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat());
	}

public:
	FOnHpZeroDelegate OnHpZero;
	FOnHpChangedDelegate OnHpChanged;
	FOnStatChangedDelegate OnStatChanged;

private:
	UPROPERTY(VisibleAnywhere, Category = Stat)
	float CurrentLevel;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float CurrentHp;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	FB1CharacterStat BaseStat;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	FB1CharacterStat ModifierStat;
};
