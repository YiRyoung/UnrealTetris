// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BlockDataTable.generated.h"

USTRUCT(BlueprintType)
struct FBlockDataRow : public FTableRowBase
{
	GENERATED_BODY()

	FBlockDataRow() {}
	~FBlockDataRow() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlockShape")
	UStaticMesh* Shape = nullptr;
};
UCLASS()
class TETRIS_P_API UBlockDataTable : public UObject
{
	GENERATED_BODY()
	
};
