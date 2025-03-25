// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/PlayPawn.h"

// Sets default values
APlayPawn::APlayPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayPawn::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnPos = FVector({ -UGlobal::GetBlockSize() * ((UGlobal::GetRows() * 0.5f) - 4), 0.0f, 0.0f });
	SpawnBlock();
}

// Called every frame
void APlayPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


int APlayPawn::SetBlockType()
{
	return FMath::RandRange(0, 6);
}

void APlayPawn::SpawnBlock()
{
	if (!GetWorld()) { return; }

	int BlockType = SetBlockType();

	AActor* NewBlock = GetWorld()->SpawnActor<AActor>(ATetrisBlock::StaticClass(), SpawnPos, FRotator::ZeroRotator);
	if (NewBlock)
	{
		ATetrisBlock* TetrisBlock = Cast<ATetrisBlock>(NewBlock);
		if (TetrisBlock)
		{
			TetrisBlock->InitBlock(BlockType);
		}
	}
}
