// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TetrisBlock.generated.h"

UENUM(BlueprintType)
enum class  EBlockType : uint8
{
	I,
	J,
	L,
	O,
	S,
	T,
	Z
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlockType")
	EBlockType BlockType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BlockType")
	UStaticMeshComponent* MeshComponent;

	void InitBlock();
};