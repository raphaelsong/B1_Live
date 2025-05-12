// Fill out your copyright notice in the Description page of Project Settings.


#include "GameData/B1GameSingleton.h"
#include "GameData/B1CharacterStat.h"

UB1GameSingleton::UB1GameSingleton()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableRef(TEXT("/Script/Engine.DataTable'/Game/GameData/DT_B1CharacterStat.DT_B1CharacterStat'"));
	if (DataTableRef.Succeeded())
	{
		const UDataTable* DataTable = DataTableRef.Object;
		check(DataTable->GetRowMap().Num() > 0);

		TArray<uint8*> ValueArray;
		DataTable->GetRowMap().GenerateValueArray(ValueArray);
		Algo::Transform(ValueArray, CharacterStatTable,
			[](uint8* Value)
			{
				return *reinterpret_cast<FB1CharacterStat*>(Value);
			}
		);
	}

	CharacterMaxLevel = CharacterStatTable.Num();
	ensure(CharacterMaxLevel > 0);
}

UB1GameSingleton& UB1GameSingleton::Get()
{
	UB1GameSingleton* Singleton = CastChecked<UB1GameSingleton>(GEngine->GameSingleton);
	if (Singleton)
	{
		return *Singleton;
	}

	UE_LOG(LogTemp, Error, TEXT("Invalid Game Singleton"));
	return *NewObject<UB1GameSingleton>();
}

FB1CharacterStat UB1GameSingleton::GetCharacterStat(int32 InLevel) const
{
	if (CharacterStatTable.IsValidIndex(InLevel - 1))
	{
		return CharacterStatTable[InLevel - 1];
	}
	else
	{
		return FB1CharacterStat();
	}
}
