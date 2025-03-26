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
            Subsystem->AddMappingContext(MappingContext, 0); // 매핑 컨텍스트 추가
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

    // Enhanced Input Component 캐스팅
    UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    if (EnhancedInputComponent)
    {
        // 입력 액션을 함수에 바인딩
        EnhancedInputComponent->BindAction(IA_MoveLeft, ETriggerEvent::Started, this, &APlayPawn::MoveLeft);
        EnhancedInputComponent->BindAction(IA_MoveRight, ETriggerEvent::Started, this, &APlayPawn::MoveRight);
        EnhancedInputComponent->BindAction(IA_MoveDown, ETriggerEvent::Started, this, &APlayPawn::MoveDown);
        EnhancedInputComponent->BindAction(IA_Rotate, ETriggerEvent::Started, this, &APlayPawn::Rotate);
    }

}

void APlayPawn::MoveLeft()
{

    UE_LOG(LogTemp, Warning, TEXT("Input Left"));
}

void APlayPawn::MoveRight()
{
}

void APlayPawn::MoveDown()
{
}

void APlayPawn::Rotate()
{
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
}

void APlayPawn::UpdateBoard()
{
    TArray<FVector2D> WorldPositions = CurrentBlock.GetWorldCells();
    
    for (const FVector2D& Position : WorldPositions)
    {
        int BoardX = -(Position.X - (UGlobal::BlockSize * ((UGlobal::Rows / 2) - 1))) / UGlobal::BlockSize;
        int BoardY = (Position.Y + (UGlobal::BlockSize * ((UGlobal::Columns / 2) - 1))) / UGlobal::BlockSize;

        UE_LOG(LogTemp, Log, TEXT("Block Cell at Board Position: (%d, %d)"), BoardX, BoardY);
        TetrisBoard->AddBlock(BoardX, BoardY);
        TetrisBoard->DrawBoard();
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