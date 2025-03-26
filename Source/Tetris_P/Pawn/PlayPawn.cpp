// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/PlayPawn.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Actor/TetrisBoard.h"
#include "Actor/PlayBlock.h"
#include "Engine/World.h"

// Sets default values
APlayPawn::APlayPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayPawn::BeginPlay()
{
	Super::BeginPlay();

	InitializeGame();
}

// Called every frame
void APlayPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayPawn::InitializeGame()
{
    if (!TetrisBoard && TetrisBoardBlueprint)
    {
        TetrisBoard = GetWorld()->SpawnActor<ATetrisBoard>(TetrisBoardBlueprint, FTransform::Identity);

        if (TetrisBoard)
        {
            TetrisBoard->InitBoard();
        }
    }

    SpawnLogicBlock();
}

void APlayPawn::SpawnLogicBlock()
{
   EBlockType CurType = SetBlockType();
   FVector2D InitialPivot = { UGlobal::BlockSize * ((UGlobal::Rows * 0.5f) - 1), 0.0f };
   CurrentBlock.InitializeLogic(CurType, InitialPivot);

   PrintBlockWorldPos();
   SpawnVisualBlock();
   ConvertBoardPos();
}

void APlayPawn::ConvertBoardPos()
{
    TArray<FVector2D> WorldPositions = CurrentBlock.GetWorldCells();
    
    for (const FVector2D& Position : WorldPositions)
    {
        float BoardX = -(Position.X - (UGlobal::BlockSize * ((UGlobal::Rows / 2) - 1))) / UGlobal::BlockSize;
        float BoardY = (Position.Y + (UGlobal::BlockSize * ((UGlobal::Columns / 2) - 1))) / UGlobal::BlockSize;

        UE_LOG(LogTemp, Log, TEXT("Block Cell at Board Position: (%f, %f)"), BoardX, BoardY);
    }
}

void APlayPawn::SpawnVisualBlock()
{
    TArray<FVector2D> WorldPositions = CurrentBlock.GetWorldCells();

    for (const FVector2D& Position : WorldPositions)
    {
        GetWorld()->SpawnActor<AActor>(PlayBlockBlueprint, FVector{Position.X, Position.Y, 0.0f}, FRotator::ZeroRotator);
    }
}

void APlayPawn::PrintBlockWorldPos()
{
    TArray<FVector2D> WorldPositions = CurrentBlock.GetWorldCells();

    for (const FVector2D& Position_W : WorldPositions)
    {
        UE_LOG(LogTemp, Log, TEXT("Block Cell at World Position: (%f, %f)"), Position_W.X, Position_W.Y);
    }
}