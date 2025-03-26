// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global/Global.h"
#include "TetrisBlock.generated.h"

UENUM(BlueprintType)
enum class EBlockType : uint8
{
	I_BLOCK UMETA(DisplayName = "I Block"),
	O_BLOCK UMETA(DisplayName = "O Block"),
	T_BLOCK UMETA(DisplayName = "T Block"),
	S_BLOCK UMETA(DisplayName = "S Block"),
	Z_BLOCK UMETA(DisplayName = "Z Block"),
	J_BLOCK UMETA(DisplayName = "J Block"),
	L_BLOCK UMETA(DisplayName = "L Block")
};

USTRUCT(BlueprintType)
struct FBlockLogic
{
	GENERATED_BODY()

public:
	FVector2D RelativePivot;
	FVector2D WorldPivot;
	TArray<FVector2D> RelativeCells;

	TArray<FVector2D> GetWorldCells() const;

	void InitializeLogic(EBlockType BlockType, FVector2D InitialPivot);

	void MoveByOffset(const FVector2D& Offset);

	bool CanMove(const FBlockLogic& BlockLogic, const TArray<TArray<int32>>& Board, FVector2D Direction);
	void Move(FVector2D Direction);

	bool CanRotate(const FBlockLogic& BlockLogic, const TArray<TArray<int32>>& Board);
	void Rotate();
};

UCLASS()
class TETRIS_P_API ATetrisBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATetrisBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
};