// Fill out your copyright notice in the Description page of Project Settings.

#include "ZISQLiteBP.h"
#include "ZISQLite.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ZISQLiteLibrary/sqlite3.h"



int32 UZISQLiteBP::GetInt(int32 a, int32 b)
{
	return a + b;
}

//GetAllActorsWithComponent(const UObject* WorldContextObject, const TSubclassOf<UActorComponent> component, TArray<AActor*> &outActors, TArray<UActorComponent*> outActorsComponent)
