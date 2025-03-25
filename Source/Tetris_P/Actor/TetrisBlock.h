// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global/Global.h"
#include "TetrisBlock.generated.h"

USTRUCT(BlueprintType)
struct FBlockLogic
{
	GENERATED_BODY()

	FVector2D Pivot;
	TArray<FVector2D> RelativeCells;
};

UENUM(BlueprintType)
enum class  EBlockType : uint8
{
	I_BLOCK,
	J_BLOCK,
	L_BLOCK,
	O_BLOCK,
	S_BLOCK,
	T_BLOCK,
	Z_BLOCK
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
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "BlockSize")
	float BlockSize = UGlobal::GetBlockSize();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlockType")
	EBlockType BlockType = EBlockType::I_BLOCK;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BlockType")
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BlockLogic")
	FBlockLogic LogicData;

	void InitLogicBlock(int TypeCase);
	void InitVisualBlock(int TypeCase);
};