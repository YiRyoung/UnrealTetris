// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "MaterialDataTable.h"
#include "Materials/MaterialInterface.h"
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
	static UMaterialInterface* GetMaterial(const FString& MatName);
};
