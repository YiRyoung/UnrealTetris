// Fill out your copyright notice in the Description page of Project Settings.


#include "Global.h"

UStaticMesh* UGlobal::GetBlockMesh(const FString& BlockName)
{
	UDataTable* BlockDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DT_BlockDataTable.DT_BlockDataTable"));

	if (!BlockDataTable)
	{
		UE_LOG(LogTemp, Fatal, TEXT("BlockDataTable not found!"));
		return nullptr;
	}

	FName RowName = FName(*BlockName);
	FBlockDataRow* BlockData = BlockDataTable->FindRow<FBlockDataRow>(RowName, TEXT(""));

	if (BlockData)
	{
		return BlockData->Shape;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("BlockData not found for: %s"), *BlockName);
		return nullptr;
	}
}
