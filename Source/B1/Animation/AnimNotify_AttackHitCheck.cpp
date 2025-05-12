// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_AttackHitCheck.h"
#include "Interface/B1AttackInterface.h"

void UAnimNotify_AttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IB1AttackInterface* AttackInterface = Cast<IB1AttackInterface>(MeshComp->GetOwner());
		if (AttackInterface)
		{
			AttackInterface->AttackHitCheck();
		}
	}
}
