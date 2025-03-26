// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Actor/TetrisBlock.h"
#include "InputMappingContext.h"
#include "Global/Global.h"
#include "PlayPawn.generated.h"

UCLASS()
class TETRIS_P_API APlayPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputMappingContext* MappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_MoveLeft;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_MoveRight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_MoveDown;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_Rotate;

	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void Rotate();

	// Board & Block
	UPROPERTY()
	class ATetrisBoard* TetrisBoard;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ATetrisBoard> TetrisBoardBlueprint;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APlayBlock> PlayBlockBlueprint;

	void InitializeGame();

private:
	FBlockLogic CurrentBlock;
	TArray<AActor*> SpawnedVisualBlocks;

	EBlockType SetBlockType()
	{
		int TypeNum = FMath::RandRange(0, 6);
		return static_cast<EBlockType>(TypeNum);
	}

	void SpawnLogicBlock();
	
	void ClearPreviousBlockPos();
	void UpdateBoard();

	void SpawnVisualBlock();

	void UpdateVisualBlock();

	void PrintBlockWorldPos();
};
