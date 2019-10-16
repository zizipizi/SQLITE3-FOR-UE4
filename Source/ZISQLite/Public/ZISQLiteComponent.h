// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZISQLiteComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FQueryComplitedPin);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZISQLITE_API UZISQLiteComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UZISQLiteComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	static int callback(void *data, int argc, char **argv, char **Colname);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintPure, Category = "ZISQLite")
		FString returnString();

	UFUNCTION(BlueprintCallable, Category = "ZISQLite")
		bool InsertData(FString Query);

	UFUNCTION(BlueprintCallable, Category = "ZISQLite")
		FString Query(FString query, int32 columnNumber);

private:
	void CreateDataBase();
	int rc = 0;
	sqlite3 *dataBase;
	FString path;
};
