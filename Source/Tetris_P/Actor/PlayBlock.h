// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayBlock.generated.h"

UCLASS()
class TETRIS_P_API APlayBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PlayBlock")
	UStaticMeshComponent* PlayBlock;

private:
	FString Mat = TEXT("/Game/Resources/Materials/MAT_Block.MAT_Block");
	FString Block = TEXT("/Game/Resources/Block/box.box");
};
