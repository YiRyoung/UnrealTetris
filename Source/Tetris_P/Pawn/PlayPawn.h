// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Actor/TetrisBlock.h"
#include "Actor/TetrisBoard.h"
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
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Spawn")
	FVector SpawnPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATetrisBlock* CurrentBlock;

	int SetBlockType();

	void SpawnBlock();

};
