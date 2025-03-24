// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisBoard.h"

// Sets default values
ATetrisBoard::ATetrisBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ConstructorHelpers::FClassFinder<AActor> BoundaryBlockBP(TEXT("/Game/Blueprints/BP_BoundaryBlock"));
	if (BoundaryBlockBP.Succeeded())
	{
		BoundaryBlockClass = BoundaryBlockBP.Class;
	}
}

// Called when the game starts or when spawned
void ATetrisBoard::BeginPlay()
{
	Super::BeginPlay();

	InitBoard();
	DrawOutLine(GetWorld(), Rows, Columns, BlockSize);


}

void ATetrisBoard::InitBoard()
{
	Board.SetNum(Rows);
	for (int Row = 0; Row < Rows; ++Row)
	{
		Board[Row].SetNum(Columns);
		for (int Col = 0; Col < Columns; ++Col)
		{
			Board[Row][Col] = 0;
		}
	}
}

void ATetrisBoard::DrawOutLine(UWorld* World, int Row, int Column, float Size)
{
	if (!BoundaryBlockClass) { return; }

	FVector BoardCenter = CalculateBoardCenter(Rows, Columns, BlockSize);

	for (int i = 0; i <= Rows; ++i)
	{
		FVector LeftPosition = BoardCenter + FVector(i * BlockSize, 0.0f, 0.0f);
		FVector RightPosition = BoardCenter + FVector(i * BlockSize, Columns * BlockSize, 0.0f);

		World->SpawnActor<AActor>(BoundaryBlockClass, LeftPosition, FRotator::ZeroRotator);
		World->SpawnActor<AActor>(BoundaryBlockClass, RightPosition, FRotator::ZeroRotator);
	}

	for (int j = 0; j <= Columns; ++j)
	{
		FVector TopPosition = BoardCenter + FVector(0.0f, j * BlockSize, 0.0f);
		FVector BottomPosition = BoardCenter + FVector(Rows * BlockSize, j * BlockSize, 0.0f);

		World->SpawnActor<AActor>(BoundaryBlockClass, TopPosition, FRotator::ZeroRotator);
		World->SpawnActor<AActor>(BoundaryBlockClass, BottomPosition, FRotator::ZeroRotator);
	}

}

FVector ATetrisBoard::CalculateBoardCenter(int Row, int Column, float Size)
{
	float StartX = -(Rows / 2.0f) * BlockSize;
	float StartY = -(Columns / 2.0f) * BlockSize;
	return FVector(StartX, StartY, 0.0f);

}

