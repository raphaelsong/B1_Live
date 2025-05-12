// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage/B1StageGimmick.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/OverlapResult.h"
#include "Character/B1Monster.h"
#include "Item/B1ItemBox.h"

// Sets default values
AB1StageGimmick::AB1StageGimmick()
{
	// Stage Section
	CurrentStageLevel = 0;

	StageMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StageMesh"));
	SetRootComponent(StageMesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StageMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/_Art/Environment/Stages/SM_SQUARE.SM_SQUARE'"));
	if (StageMeshRef.Succeeded())
	{
		StageMesh->SetStaticMesh(StageMeshRef.Object);
	}

	StageTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("StageTriggerBox"));
	StageTriggerBox->SetupAttachment(GetRootComponent());
	StageTriggerBox->SetBoxExtent(FVector(775.0f, 775.0f, 300.0f));
	StageTriggerBox->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
	StageTriggerBox->SetCollisionProfileName(FName("B1Trigger"));
	StageTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AB1StageGimmick::OnStageTriggerBoxBeginOverlap);

	// Gate Section
	static ConstructorHelpers::FObjectFinder<UStaticMesh> GateMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/_Art/Environment/Props/SM_GATE.SM_GATE'"));

	static FName GateSockets[] = { TEXT("+XGate"), TEXT("-XGate"), TEXT("+YGate"), TEXT("-YGate") };
	for (FName GateSocket : GateSockets)
	{
		UStaticMeshComponent* GateMesh = CreateDefaultSubobject<UStaticMeshComponent>(GateSocket);
		GateMesh->SetupAttachment(StageMesh, GateSocket);
		GateMesh->SetStaticMesh(GateMeshRef.Object);
		GateMesh->SetRelativeLocation(FVector(0.0f, -80.5f, 0.0f));
		GateMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		GateMeshes.Add(GateSocket, GateMesh);

		FName TriggerBoxName = *GateSocket.ToString().Append(TEXT("TriggerBox"));
		UBoxComponent* GateTriggerBox = CreateDefaultSubobject<UBoxComponent>(TriggerBoxName);
		GateTriggerBox->SetupAttachment(StageMesh, GateSocket);
		GateTriggerBox->SetBoxExtent(FVector(100.0f, 100.0f, 300.0f));
		GateTriggerBox->SetRelativeLocation(FVector(70.0f, 0.0f, 250.0f));
		GateTriggerBox->SetCollisionProfileName(FName("B1Trigger"));
		GateTriggerBox->ComponentTags.Add(GateSocket);
		GateTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AB1StageGimmick::OnGateTriggerBoxBeginOverlap);
		GateTriggerBoxes.Add(GateTriggerBox);
	}

	// GameState Section
	CurrentState = EStageState::READY;

	StateChangeActions.Add(EStageState::READY, FOnStateChangedDelegate::CreateUObject(this, &AB1StageGimmick::SetReady));
	StateChangeActions.Add(EStageState::FIGHT, FOnStateChangedDelegate::CreateUObject(this, &AB1StageGimmick::SetFight));
	StateChangeActions.Add(EStageState::REWARD, FOnStateChangedDelegate::CreateUObject(this, &AB1StageGimmick::SetChooseReward));
	StateChangeActions.Add(EStageState::NEXT, FOnStateChangedDelegate::CreateUObject(this, &AB1StageGimmick::SetChooseNext));

	// FightState Section
	static ConstructorHelpers::FClassFinder<AB1Monster> MonsterClassRef(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_B1Monster.BP_B1Monster_C'"));
	if (MonsterClassRef.Succeeded())
	{
		MonsterClass = MonsterClassRef.Class;
	}

	// RewardState Section
	RewardBoxClass = AB1ItemBox::StaticClass();

	static FName RewardSockets[] = { TEXT("+XReward"), TEXT("-XReward"), TEXT("+YReward"), TEXT("-YReward") };

	for (FName RewardSocket : RewardSockets)
	{
		FVector RewardLocation = StageMesh->GetSocketLocation(RewardSocket);
		RewardBoxLocations.Add(RewardSocket, RewardLocation);
	}
}

void AB1StageGimmick::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	SetState(CurrentState);
}

void AB1StageGimmick::OnStageTriggerBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SetState(EStageState::FIGHT);
}

void AB1StageGimmick::OnGateTriggerBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	check(OverlappedComponent->ComponentTags.Num() == 1);
	FName ComponentTag = OverlappedComponent->ComponentTags[0];
	FName SocketName = FName(*ComponentTag.ToString().Left(2));
	check(StageMesh->DoesSocketExist(SocketName));

	FVector NewLocation = StageMesh->GetSocketLocation(SocketName);
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam;
	CollisionQueryParam.AddIgnoredActor(this);

	bool bResult = GetWorld()->OverlapMultiByObjectType(
		OverlapResults,
		NewLocation,
		FQuat::Identity,
		FCollisionObjectQueryParams::InitType::AllObjects,
		FCollisionShape::MakeSphere(775.0f),
		CollisionQueryParam
	);

	if (!bResult)
	{
		FTransform NewTransform(NewLocation);
		AB1StageGimmick* NewGimmick = GetWorld()->SpawnActorDeferred<AB1StageGimmick>(AB1StageGimmick::StaticClass(), NewTransform);

		if (NewGimmick)
		{
			NewGimmick->SetStageLevel(CurrentStageLevel + 1);
			NewGimmick->FinishSpawning(NewTransform);
		}
	}
}

void AB1StageGimmick::OpenAllGates()
{
	for (const auto GateMesh : GateMeshes)
	{
		(GateMesh.Value)->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	}
}

void AB1StageGimmick::CloseAllGates()
{
	for (const auto GateMesh : GateMeshes)
	{
		(GateMesh.Value)->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	}
}

void AB1StageGimmick::SetState(EStageState InNewState)
{
	CurrentState = InNewState;

	if (StateChangeActions.Contains(CurrentState))
	{
		StateChangeActions[CurrentState].ExecuteIfBound();
	}
}

void AB1StageGimmick::SetReady()
{
	StageTriggerBox->SetCollisionProfileName(FName("B1Trigger"));
	for (auto GateTriggerBox : GateTriggerBoxes)
	{
		GateTriggerBox->SetCollisionProfileName(FName("NoCollision"));
	}

	OpenAllGates();
}

void AB1StageGimmick::SetFight()
{
	StageTriggerBox->SetCollisionProfileName(FName("NoCollision"));
	for (auto GateTriggerBox : GateTriggerBoxes)
	{
		GateTriggerBox->SetCollisionProfileName(FName("NoCollision"));
	}

	CloseAllGates();

	GetWorld()->GetTimerManager().SetTimer(MonsterSpawnTimerHandle, this, &AB1StageGimmick::OnMonsterSpawn, MonsterSpawnTime, false);
}

void AB1StageGimmick::SetChooseReward()
{
	StageTriggerBox->SetCollisionProfileName(FName("NoCollision"));
	for (auto GateTriggerBox : GateTriggerBoxes)
	{
		GateTriggerBox->SetCollisionProfileName(FName("NoCollision"));
	}
	CloseAllGates();

	SpawnRewardBoxes();
}

void AB1StageGimmick::SetChooseNext()
{
	StageTriggerBox->SetCollisionProfileName(FName("NoCollision"));
	for (auto GateTriggerBox : GateTriggerBoxes)
	{
		GateTriggerBox->SetCollisionProfileName(FName("B1Trigger"));
	}

	OpenAllGates();
}

void AB1StageGimmick::OnMonsterSpawn()
{
	const FTransform SpawnTransform(GetActorLocation() + FVector::UpVector * 88.0f);
	AB1Monster* NewMonster = GetWorld()->SpawnActorDeferred<AB1Monster>(MonsterClass, SpawnTransform);
	if (NewMonster)
	{
		NewMonster->OnDestroyed.AddDynamic(this, &AB1StageGimmick::OnMonsterDestroyed);
		NewMonster->SetLevel(CurrentStageLevel);
		NewMonster->FinishSpawning(SpawnTransform);
	}
}

void AB1StageGimmick::OnMonsterDestroyed(AActor* DestroyedActor)
{
	SetState(EStageState::REWARD);
}

void AB1StageGimmick::SpawnRewardBoxes()
{
	for (const auto& RewardBoxLocation : RewardBoxLocations)
	{
		FTransform SpawnTranform(GetActorLocation() + RewardBoxLocation.Value + FVector(0.0f, 0.0f, 30.0f));
		AB1ItemBox* RewardBoxActor = GetWorld()->SpawnActorDeferred<AB1ItemBox>(RewardBoxClass, SpawnTranform);
		if (RewardBoxActor)
		{
			RewardBoxActor->Tags.Add(RewardBoxLocation.Key);
			RewardBoxActor->GetTriggerBox()->OnComponentBeginOverlap.AddDynamic(this, &AB1StageGimmick::OnRewardTriggerBoxBeginOverlap);

			RewardBoxes.Add(RewardBoxActor);
		}
	}

	for (const auto& RewardBox : RewardBoxes)
	{
		if (RewardBox.IsValid())
		{
			RewardBox.Get()->FinishSpawning(RewardBox.Get()->GetActorTransform());
		}
	}
}

void AB1StageGimmick::OnRewardTriggerBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for (const auto& RewardBox : RewardBoxes)
	{
		if (RewardBox.IsValid())
		{
			AB1ItemBox* ValidItemBox = RewardBox.Get();
			AActor* OverlappedBox = OverlappedComponent->GetOwner();
			if (OverlappedBox != ValidItemBox)
			{
				ValidItemBox->Destroy();
			}
		}
	}

	SetState(EStageState::NEXT);
}
