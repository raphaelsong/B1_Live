// Fill out your copyright notice in the Description page of Project Settings.


#include "System/B1GameMode.h"
#include "Player/B1PlayerController.h"

AB1GameMode::AB1GameMode()
{
    ClearScore = 3;
    CurrentScore = 0;
    bIsCleared = false;
}

void AB1GameMode::OnPlayerScoreChanged(int32 NewPlayerScore)
{
    CurrentScore = NewPlayerScore;
    
    AB1PlayerController* B1PlayerController = Cast<AB1PlayerController>(GetWorld()->GetFirstPlayerController());
    if (B1PlayerController)
    {
        B1PlayerController->GameScoreChanged(CurrentScore);
    }

    if (CurrentScore >= ClearScore)
    {
        bIsCleared = true;

        if (B1PlayerController)
        {
            B1PlayerController->GameClear();
        }
    }
}

void AB1GameMode::OnPlayerDead()
{
    AB1PlayerController* B1PlayerController = Cast<AB1PlayerController>(GetWorld()->GetFirstPlayerController());
    if (B1PlayerController)
    {
        B1PlayerController->GameOver();
    }
}

bool AB1GameMode::IsGameCleared()
{
    return bIsCleared;
}

void AB1GameMode::AddPlyerScore(int32 AddPlayerScore)
{
    CurrentScore += AddPlayerScore;

    AB1PlayerController* B1PlayerController = Cast<AB1PlayerController>(GetWorld()->GetFirstPlayerController());
    if (B1PlayerController)
    {
        B1PlayerController->GameScoreChanged(CurrentScore);
    }

    if (CurrentScore >= ClearScore)
    {
        bIsCleared = true;

        if (B1PlayerController)
        {
            B1PlayerController->GameClear();
        }
    }
}
