// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/B1Box.h"

// Sets default values
AB1Box::AB1Box()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	RootComponent = Box;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/_Art/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube'"));
	if (BoxMeshRef.Succeeded())
	{
		Box->SetStaticMesh(BoxMeshRef.Object);
	}

	Box->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
}

// Called when the game starts or when spawned
void AB1Box::BeginPlay()
{
	Super::BeginPlay();
	
	Box->OnComponentHit.AddDynamic(this, &AB1Box::OnHit);
}

// Called every frame
void AB1Box::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AB1Box::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}

