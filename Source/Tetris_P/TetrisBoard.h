// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Block")
	float BlockSize = 85.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
	int Rows = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
	int Columns = 10;

	void InitBoard();

	void DrawOutLine(UWorld* World, int Row, int Column, float Size);

	FVector CalculateBoardCenter(int Row, int Column, float Size);

private:
	TArray<TArray<int>> Board;
};
