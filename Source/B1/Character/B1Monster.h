// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/B1CharacterBase.h"
#include "Interface/B1AIAttackInterface.h"
#include "Engine/StreamableManager.h"
#include "B1Monster.generated.h"

/**
 * 
 */
UCLASS(config = Monster)
class B1_API AB1Monster : public AB1CharacterBase, public IB1AIAttackInterface
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	AB1Monster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void PostInitializeComponents() override;
	void MonsterMeshLoadCompleted();

public: 
	virtual void SetDead() override;

	// Inherited via IB1AIAttackInterface
	virtual float GetAttackRange() override;

	// Inherited via IB1AIAttackInterface
	virtual void AttackByAI() override;

	// Inherited via IB1AIAttackInterface
	virtual void SetAIAttackDelegate(const FAIAttackFinished& InOnAttackFinished) override;

	virtual void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsPropertyEnded) override;
protected:
	float DeadEventDelayTime = 5.0f;

	FAIAttackFinished OnAttackFinished;

protected:
	UPROPERTY(Config)
	TArray<FSoftObjectPath> MonsterMeshes;

	TSharedPtr<FStreamableHandle> MonsterMeshHandle;
};
