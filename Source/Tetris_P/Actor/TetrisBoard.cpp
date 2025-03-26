// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisBoard.h"
#include "TetrisBlock.h"
#include "Global/Global.h"

// Sets default values
ATetrisBoard::ATetrisBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATetrisBoard::BeginPlay()
{
	Super::BeginPlay();

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

	DrawOutLine(GetWorld(), Rows, Columns, UGlobal::BlockSize);
}

void ATetrisBoard::DrawOutLine(UWorld* World, int Row, int Column, float Size)
{
	if (!BoundaryBlockClass) { return; }

	FVector BoardCenter = CalculateBoardCenter(Rows, Columns, UGlobal::BlockSize);

	for (int i = 0; i <= Row + 1; ++i)
	{
		FVector LeftPosition = BoardCenter + FVector(i * Size, 0, 0.0f);
		FVector RightPosition = BoardCenter + FVector(i * Size, (Column + 1) * Size, 0.0f);

		World->SpawnActor<AActor>(BoundaryBlockClass, LeftPosition, FRotator::ZeroRotator);
		World->SpawnActor<AActor>(BoundaryBlockClass, RightPosition, FRotator::ZeroRotator);
	}

	for (int j = 0; j <= Column + 1; ++j)
	{
		FVector BottomPosition = BoardCenter + FVector(0, j * Size, 0.0f);
		FVector TopPosition = BoardCenter + FVector((Row + 1) * Size, j * Size, 0.0f);

		World->SpawnActor<AActor>(BoundaryBlockClass, TopPosition, FRotator::ZeroRotator);
		World->SpawnActor<AActor>(BoundaryBlockClass, BottomPosition, FRotator::ZeroRotator);
	}
}

FVector ATetrisBoard::CalculateBoardCenter(int Row, int Column, float Size)
{
	float StartX = -((Rows + 2) / 2.0f) * UGlobal::BlockSize;
	float StartY = -(Columns / 2.0f) * UGlobal::BlockSize;
	return FVector(StartX, StartY, 0.0f);
}

void ATetrisBoard::DrawBoard()
{
	// 로그를 통해 보드의 현재 상태를 출력
	UE_LOG(LogTemp, Log, TEXT("Current Board State:"));

	for (int Row = 0; Row < Rows; ++Row) // 모든 행 순회
	{
		FString RowData; // 한 행의 데이터를 저장할 문자열

		for (int Col = 0; Col < Columns; ++Col) // 각 열 순회
		{
			RowData += FString::FromInt(Board[Row][Col]) + TEXT(" "); // 각 칸의 데이터를 추가
		}

		// 각 행 출력
		UE_LOG(LogTemp, Log, TEXT("Row %d: %s"), Row, *RowData);
	}

}

void ATetrisBoard::AddBlock(int X, int Y)
{
	Board[X][Y] = 1;
}

void ATetrisBoard::DeleteBlock(int X, int Y)
{
	Board[X][Y] = 0;
}