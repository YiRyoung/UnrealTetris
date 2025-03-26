// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/PlayPawn.h"
#include "Actor/TetrisBoard.h"
#include "Actor/PlayBlock.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
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

    APlayerController* PlayerController = Cast<APlayerController>(GetController());
    if (PlayerController)
    {
        UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
        if (Subsystem && MappingContext)
        {
            Subsystem->AddMappingContext(MappingContext, 0);
        }
    }
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

    UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    if (EnhancedInputComponent)
    {
        EnhancedInputComponent->BindAction(IA_MoveLeft, ETriggerEvent::Started, this, &APlayPawn::MoveLeft);
        EnhancedInputComponent->BindAction(IA_MoveRight, ETriggerEvent::Started, this, &APlayPawn::MoveRight);
        EnhancedInputComponent->BindAction(IA_MoveDown, ETriggerEvent::Started, this, &APlayPawn::MoveDown);
        EnhancedInputComponent->BindAction(IA_Rotate, ETriggerEvent::Started, this, &APlayPawn::Rotate);
    }

}

void APlayPawn::MoveLeft()
{
    UE_LOG(LogTemp, Warning, TEXT("Input Left"));
    FVector2D Offset(0, -1);
    CurrentBlock.MoveByOffset(Offset);
    UpdateVisualBlock();
    UpdateBoard();
    TetrisBoard->DrawBoard();
}

void APlayPawn::MoveRight()
{
    UE_LOG(LogTemp, Warning, TEXT("Input Right"));
    FVector2D Offset(0, 1);
    CurrentBlock.MoveByOffset(Offset);
    UpdateVisualBlock();
    UpdateBoard();
    TetrisBoard->DrawBoard();
}

void APlayPawn::MoveDown()
{
    UE_LOG(LogTemp, Warning, TEXT("Input Down"));
    FVector2D Offset(-1, 0);
    CurrentBlock.MoveByOffset(Offset);
    UpdateVisualBlock();
    UpdateBoard();
    TetrisBoard->DrawBoard();
}

void APlayPawn::Rotate()
{
    CurrentBlock.Rotate();
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
   UpdateBoard();
   PreviousWorldPositions = CurrentBlock.GetWorldCells();
}


void APlayPawn::ClearPreviousBlockPos()
{
    for (const FVector2D& Position : PreviousWorldPositions)
    {
        int BoardX = -(Position.X - (UGlobal::BlockSize * ((UGlobal::Rows / 2) - 1))) / UGlobal::BlockSize;
        int BoardY = (Position.Y + (UGlobal::BlockSize * ((UGlobal::Columns / 2) - 1))) / UGlobal::BlockSize;
        TetrisBoard->DeleteBlock(BoardX, BoardY);

        UE_LOG(LogTemp, Log, TEXT("Cleared Block at Previous Position: (%d, %d)"), BoardX, BoardY);
    }
}

void APlayPawn::UpdateBoard()
{
    ClearPreviousBlockPos();

    PreviousWorldPositions = CurrentBlock.GetWorldCells();

    for (const FVector2D& Position : PreviousWorldPositions)
    {
        int BoardX = -(Position.X - (UGlobal::BlockSize * ((UGlobal::Rows / 2) - 1))) / UGlobal::BlockSize;
        int BoardY = (Position.Y + (UGlobal::BlockSize * ((UGlobal::Columns / 2) - 1))) / UGlobal::BlockSize;

        TetrisBoard->AddBlock(BoardX, BoardY);
        UE_LOG(LogTemp, Log, TEXT("Updated Block at New Position: (%d, %d)"), BoardX, BoardY);
    }
}


void APlayPawn::SpawnVisualBlock()
{
    TArray<FVector2D> WorldPositions = CurrentBlock.GetWorldCells();

    for (const FVector2D& Position : WorldPositions)
    {
        AActor* VisualBlock = GetWorld()->SpawnActor<AActor>(PlayBlockBlueprint, FVector(Position.X, Position.Y, 0.0f), FRotator::ZeroRotator);

        if (VisualBlock)
        {
            SpawnedVisualBlocks.Add(VisualBlock);
        }
    }
}

void APlayPawn::UpdateVisualBlock()
{
    TArray<FVector2D> WorldPositions = CurrentBlock.GetWorldCells();

    for (int i = 0; i < SpawnedVisualBlocks.Num(); ++i)
    {
        if (i < WorldPositions.Num() && SpawnedVisualBlocks[i])
        {
            FVector NewLocation = FVector(WorldPositions[i].X, WorldPositions[i].Y, 0.0f);
            SpawnedVisualBlocks[i]->SetActorLocation(NewLocation);
        }
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