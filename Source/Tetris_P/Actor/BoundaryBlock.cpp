// Fill out your copyright notice in the Description page of Project Settings.


#include "BoundaryBlock.h"

// Sets default values
ABoundaryBlock::ABoundaryBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoundaryBlock = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoundaryBlock"));
	RootComponent = BoundaryBlock;
	BoundaryBlock->SetRelativeLocation({ 0, 0, 0 });

	UStaticMesh* BlockMesh = LoadObject<UStaticMesh>(nullptr, *Block);
	if (BlockMesh)
	{
		BoundaryBlock->SetStaticMesh(BlockMesh);
	}

	UMaterial* BlockMat = LoadObject<UMaterial>(nullptr, *Mat);
	if (BlockMat)
	{
		BoundaryBlock->SetMaterial(0, BlockMat);
	}
}

// Called when the game starts or when spawned
void ABoundaryBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoundaryBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

