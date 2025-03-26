// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisBlock.h"

// Sets default values
ATetrisBlock::ATetrisBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATetrisBlock::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATetrisBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<FVector2D> FBlockLogic::GetWorldCells() const
{
	TArray<FVector2D> WorldPositions;

	for (const FVector2D& RelativeCell : RelativeCells)
	{
		FVector2D WorldPosition = WorldPivot + (RelativeCell - RelativePivot) * UGlobal::BlockSize;
		WorldPositions.Add(WorldPosition);
	}

	return WorldPositions;
}

void FBlockLogic::InitializeLogic(EBlockType BlockType, FVector2D InitialPivot)
{
	WorldPivot = InitialPivot;

	switch (BlockType)
	{
	case EBlockType::I_BLOCK:
		RelativePivot = { 1, 1 };
		RelativeCells = { {1, 0}, {1, 1}, {1, 2}, {1, 3} };
		break;
	case EBlockType::O_BLOCK:
		RelativePivot = { 1, 1 };
		RelativeCells = { {0, 1}, {0, 2}, {1, 1}, {1, 2} };
		break;
	case EBlockType::T_BLOCK:
		RelativePivot = { 1, 1 };
		RelativeCells = { {1, 1}, {0, 1}, {1, 0}, {1, 2} };
		break;
	case EBlockType::S_BLOCK:
		RelativePivot = { 1, 1 };
		RelativeCells = { {0, 1}, {0, 2}, {1, 0}, {1, 1} };
		break;
	case EBlockType::Z_BLOCK:
		RelativePivot = { 1, 1 };
		RelativeCells = { {0, 0}, {0, 1}, {1, 1}, {1, 2} };
		break;
	case EBlockType::J_BLOCK:
		RelativePivot = { 2, 1 };
		RelativeCells = { {1, 0}, {2, 0}, {2, 1}, {2, 2} };
		break;
	case EBlockType::L_BLOCK:
		RelativePivot = { 2, 1 };
		RelativeCells = { {1, 2}, {2, 0}, {2, 1}, {2, 2} };
		break;
	}
}

void FBlockLogic::MoveByOffset(const FVector2D& Offset)
{
	for (FVector2D& Cell : RelativeCells)
	{
		Cell += Offset;
	}
}

bool FBlockLogic::CanMove(const FBlockLogic& BlockLogic, const TArray<TArray<int32>>& Board, FVector2D Direction)
{
	for (const FVector2D& Cell : BlockLogic.RelativeCells)
	{
		FVector2D NewWorldPos = BlockLogic.WorldPivot + Direction + (Cell - BlockLogic.RelativePivot);

		if (NewWorldPos.X < 0 || NewWorldPos.X >= Board.Num() ||
			NewWorldPos.Y < 0 || NewWorldPos.Y >= Board[0].Num() ||
			Board[NewWorldPos.X][NewWorldPos.Y] != 0)
		{
			return false;
		}
	}
	return true;
}

void FBlockLogic::Move(FVector2D Direction)
{
	WorldPivot += Direction;
}

bool FBlockLogic::CanRotate(const FBlockLogic& BlockLogic, const TArray<TArray<int32>>& Board)
{
	for (FVector2D Cell : BlockLogic.RelativeCells)
	{
		FVector2D RelativeToPivot = Cell - BlockLogic.RelativePivot;
		FVector2D RotatedCell = FVector2D(-RelativeToPivot.Y, RelativeToPivot.X) + BlockLogic.RelativePivot;
		FVector2D WorldPos = BlockLogic.WorldPivot + (RotatedCell - BlockLogic.RelativePivot);

		if (WorldPos.X < 0 || WorldPos.X >= Board.Num() ||
			WorldPos.Y < 0 || WorldPos.Y >= Board[0].Num() ||
			Board[WorldPos.X][WorldPos.Y] != 0)
		{
			return false;
		}
	}
	return true;
}

void FBlockLogic::Rotate()
{
	for (FVector2D& Cell : RelativeCells)
	{
		// 기준점(RelativePivot)을 중심으로 시계 방향 90도 회전
		FVector2D RelativeToPivot = Cell - RelativePivot;
		RelativeToPivot = FVector2D(-RelativeToPivot.Y, RelativeToPivot.X); // 회전 공식
		Cell = RelativeToPivot + RelativePivot;
	}
}
