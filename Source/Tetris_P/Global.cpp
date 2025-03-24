// Fill out your copyright notice in the Description page of Project Settings.


#include "Global.h"

UMaterialInterface* UGlobal::GetMaterial(const FString& MatName)
{
	UDataTable* MaterialDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DT_MaterialDataTable.DT_MaterialDataTable"));

	if (!MaterialDataTable)
	{
		UE_LOG(LogTemp, Fatal, TEXT("MaterialDaTable not found!"));
		return nullptr;
	}

	FName RowName = FName(*MatName);
	static const FString ContextString(TEXT("Material Lookup"));

	FMaterialDataRow* Row = MaterialDataTable->FindRow<FMaterialDataRow>(RowName, ContextString);

	if (Row && Row->Mat)
	{
		return Row->Mat;
	}

	UE_LOG(LogTemp, Warning, TEXT("Material %s not found in DataTable!"), *MatName);
	return nullptr;
}
