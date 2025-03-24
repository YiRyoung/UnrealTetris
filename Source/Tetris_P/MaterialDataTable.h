// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MaterialDataTable.generated.h"

USTRUCT(BlueprintType)
struct FMaterialDataRow : public FTableRowBase
{
	GENERATED_BODY()

	FMaterialDataRow() {}
	~FMaterialDataRow() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MAT")
	UMaterialInterface* Mat = nullptr;
};
UCLASS()
class TETRIS_P_API UMaterialDataTable : public UObject
{
	GENERATED_BODY()
	
};
