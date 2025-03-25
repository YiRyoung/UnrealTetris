// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "Data/BlockDataTable.h"
#include "Global.generated.h"

/**
 * 
 */
UCLASS()
class TETRIS_P_API UGlobal : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	static int GetRows()
	{
		return 20;
	}
	
	UFUNCTION(BlueprintCallable)
	static int GetColumns()
	{
		return 10;
	}

	UFUNCTION(BlueprintCallable)
	static float GetBlockSize() 
	{ 
		return 87.0f;
	}

	UFUNCTION(BlueprintCallable)
	static UStaticMesh* GetBlockMesh(const FString& BlockType);
};
