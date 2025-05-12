// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/B1Monster.h"
#include "Components/CapsuleComponent.h"
#include "AI/B1AIController.h"

AB1Monster::AB1Monster()
{
	// Pawn AI Controller
	AIControllerClass = AB1AIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// Capsule
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("B1Monster"));

	// Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/_Art/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard'"));
	if (MeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshRef.Object);
	}
}

void AB1Monster::BeginPlay()
{
	Super::BeginPlay();
}

void AB1Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
