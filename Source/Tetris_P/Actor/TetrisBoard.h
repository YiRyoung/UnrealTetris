// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TetrisBlock.h"
#include "Global/Global.h"
#include "TetrisBoard.generated.h"

UCLASS()
class TETRIS_P_API ATetrisBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATetrisBoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "Block")
	TSubclassOf<AActor> BoundaryBlockClass;
	
	UPROPERTY()
	int Rows = UGlobal::Rows;

	UPROPERTY()
	int Columns = UGlobal::Columns;

	void InitBoard();

	void DrawOutLine(UWorld* World, int Row, int Column, float Size);

	FVector CalculateBoardCenter(int Row, int Column, float Size);

	void DrawBoard();

	int GetBoardValue(int X, int Y) const
	{
		return Board[X][Y];
	}

	void AddBlock(int X, int Y);
	void AddLockBlock(int X, int Y);
	void DeleteBlock(int X, int Y);

private:
	TArray<TArray<int>> Board;
};
