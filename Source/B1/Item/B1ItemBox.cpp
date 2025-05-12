// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/B1ItemBox.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Interface/B1ItemInterface.h"
#include "Engine/AssetManager.h"
#include "Item/B1ItemData.h"

AB1ItemBox::AB1ItemBox()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	SetRootComponent(TriggerBox);
	TriggerBox->SetCollisionProfileName(FName("B1Trigger"));
	TriggerBox->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));
	Mesh->SetCollisionProfileName(FName("NoCollision"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("/Script/Engine.StaticMesh'/Game/_Art/Environment/Props/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1'"));
	if (MeshRef.Succeeded())
	{
		Mesh->SetStaticMesh(MeshRef.Object);
	}

	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Effect"));
	Effect->SetupAttachment(GetRootComponent());

	static ConstructorHelpers::FObjectFinder<UParticleSystem> EffectRef(TEXT("/Script/Engine.ParticleSystem'/Game/_Art/Effect/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh'"));
	if (EffectRef.Succeeded())
	{
		Effect->SetTemplate(EffectRef.Object);
		Effect->bAutoActivate = false;
	}
}

// Called when the game starts or when spawned
void AB1ItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AB1ItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AB1ItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AB1ItemBox::OnBoxBeginOverlap);

	UAssetManager& Manager = UAssetManager::Get();

	TArray<FPrimaryAssetId> Assets;
	Manager.GetPrimaryAssetIdList(TEXT("B1ItemData"), Assets);
	ensure(Assets.Num() > 0);

	int32 RandomIndex = FMath::RandRange(0, Assets.Num() - 1);
	FSoftObjectPtr AssetPtr(Manager.GetPrimaryAssetPath(Assets[RandomIndex]));
	if (AssetPtr.IsPending())
	{
		AssetPtr.LoadSynchronous();
	}

	ItemData = Cast<UB1ItemData>(AssetPtr.Get());
	ensure(ItemData);
}

void AB1ItemBox::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (nullptr == ItemData)
	{
		Destroy();
		return;
	}

	IB1ItemInterface* OverlappingActor = Cast<IB1ItemInterface>(OtherActor);
	if (OverlappingActor)
	{
		OverlappingActor->TakeItem(ItemData);
	}

	Mesh->SetHiddenInGame(true);
	SetActorEnableCollision(false);
	Effect->Activate(true);
	Effect->OnSystemFinished.AddDynamic(this, &AB1ItemBox::OnEffectFinished);
}

void AB1ItemBox::OnEffectFinished(UParticleSystemComponent* PSystem)
{
	Destroy();
}

