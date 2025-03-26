// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PlayBlock.h"

// Sets default values
APlayBlock::APlayBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayBlock = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayBlock"));
	RootComponent = PlayBlock;
	PlayBlock->SetRelativeLocation({ 0, 0, 0 });

	UStaticMesh* BlockMesh = LoadObject<UStaticMesh>(nullptr, *Block);
	if (BlockMesh)
	{
		PlayBlock->SetStaticMesh(BlockMesh);
	}

	UMaterial* BlockMat = LoadObject<UMaterial>(nullptr, *Mat);
	if (BlockMat)
	{
		PlayBlock->SetMaterial(0, BlockMat);
	}
}

// Called when the game starts or when spawned
void APlayBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

