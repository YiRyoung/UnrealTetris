// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisBlock.h"

// Sets default values
ATetrisBlock::ATetrisBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Block"));
	RootComponent = MeshComponent;
	InitVisualBlock(0);
}

// Called when the game starts or when spawned
void ATetrisBlock::BeginPlay()
{
	Super::BeginPlay();
	
	InitVisualBlock(static_cast<int>(BlockType));
}

// Called every frame
void ATetrisBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATetrisBlock::InitLogicBlock(int TypeCase)
{

}

void ATetrisBlock::InitVisualBlock(int TypeCase)
{
	switch (TypeCase)
	{
	case 0:
		MeshComponent->SetStaticMesh(UGlobal::GetBlockMesh("I"));
		MeshComponent->AddRelativeLocation({-BlockSize, 0, 0});
		break;
	case 1:
		MeshComponent->SetStaticMesh(UGlobal::GetBlockMesh("J"));
		break;
	case 2:
		MeshComponent->SetStaticMesh(UGlobal::GetBlockMesh("L"));
		MeshComponent->AddRelativeLocation({-BlockSize, -BlockSize, 0});
		break;
	case 3:
		MeshComponent->SetStaticMesh(UGlobal::GetBlockMesh("O"));
		break;
	case 4:
		MeshComponent->SetStaticMesh(UGlobal::GetBlockMesh("S"));
		MeshComponent->AddRelativeLocation({0, BlockSize * 2, 0});
		break;
	case 5:
		MeshComponent->SetStaticMesh(UGlobal::GetBlockMesh("T"));
		MeshComponent->AddRelativeLocation({0, BlockSize * 2, 0});
		break;
	case 6:
		MeshComponent->SetStaticMesh(UGlobal::GetBlockMesh("Z"));
		MeshComponent->AddRelativeLocation({0, -BlockSize, 0});
		break;
	}
}