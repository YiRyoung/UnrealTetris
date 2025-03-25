// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoundaryBlock.generated.h"

UCLASS()
class TETRIS_P_API ABoundaryBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoundaryBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "BoundaryBlock")
	UStaticMeshComponent* BoundaryBlock;

private:
	FString Mat = TEXT("/Game/Resources/Block/MAT_Boundary.MAT_Boundary");
	FString Block = TEXT("/Game/Resources/Block/Block.Block");
};
