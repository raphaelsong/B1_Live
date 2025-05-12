// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/B1Monster.h"
#include "Components/CapsuleComponent.h"
#include "AI/B1AIController.h"
#include "Engine/AssetManager.h"

AB1Monster::AB1Monster()
{
	// Pawn AI Controller
	AIControllerClass = AB1AIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// Capsule
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("B1Monster"));

	GetMesh()->SetHiddenInGame(true);
}

void AB1Monster::BeginPlay()
{
	Super::BeginPlay();
}

void AB1Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AB1Monster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ensure(MonsterMeshes.Num() > 0);
	int32 RandomIndex = FMath::RandRange(0, MonsterMeshes.Num() - 1);
	MonsterMeshHandle = UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(MonsterMeshes[RandomIndex], FStreamableDelegate::CreateUObject(this, &AB1Monster::MonsterMeshLoadCompleted));
}

void AB1Monster::MonsterMeshLoadCompleted()
{
	if (MonsterMeshHandle.IsValid())
	{
		USkeletalMesh* MonsterMesh = Cast<USkeletalMesh>(MonsterMeshHandle->GetLoadedAsset());
		if (MonsterMesh)
		{
			GetMesh()->SetSkeletalMesh(MonsterMesh);
			GetMesh()->SetHiddenInGame(false);
		}
	}

	MonsterMeshHandle->ReleaseHandle();
}

void AB1Monster::SetDead()
{
	Super::SetDead();

	AB1AIController* AIController = Cast<AB1AIController>(GetController());
	if (AIController)
	{
		AIController->StopAI();
	}

	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), DeadEventDelayTime, false);
}

float AB1Monster::GetAttackRange()
{
	return 150.0f;
}

void AB1Monster::AttackByAI()
{
	ProcessComboAttack();
}

void AB1Monster::SetAIAttackDelegate(const FAIAttackFinished& InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;
}

void AB1Monster::ComboActionEnd(UAnimMontage* TargetMontage, bool IsPropertyEnded)
{
	Super::ComboActionEnd(TargetMontage, IsPropertyEnded);
	OnAttackFinished.ExecuteIfBound();
}
