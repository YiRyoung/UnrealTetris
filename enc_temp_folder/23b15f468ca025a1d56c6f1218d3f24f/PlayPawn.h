// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Actor/TetrisBlock.h"
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
	class UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ATetrisBoard> TetrisBoardBlueprint;

	UPROPERTY()
	class ATetrisBoard* TetrisBoard;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APlayBlock> PlayBlockBlueprint;

	void InitializeGame();

private:
	FBlockLogic CurrentBlock;

	EBlockType SetBlockType()
	{
		int TypeNum = FMath::RandRange(0, 6);
		return static_cast<EBlockType>(TypeNum);
	}

	void SpawnLogicBlock();
	
	// void UpdateBoard();

	void SpawnVisualBlock(UWorld* World);

	void PrintBlockWorldPos();
};
