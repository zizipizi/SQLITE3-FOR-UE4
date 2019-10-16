// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ZISQLiteLibrary/sqlite3.h"
#include "ZISQLiteBP.generated.h"

/**
 * 
 */
UCLASS()
class ZISQLITE_API UZISQLiteBP : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "ZISQLite")
	int32 GetInt(int32 a, int32 b);
};
