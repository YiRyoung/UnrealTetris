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
	static int Rows;
	static int Columns;
	static float BlockSize;
};
