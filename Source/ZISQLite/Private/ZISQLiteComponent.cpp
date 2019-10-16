// Fill out your copyright notice in the Description page of Project Settings.


#include "ZISQLiteComponent.h"
#include "ZISQLiteLibrary/sqlite3.h"
//#include "Runtime/Core/Public/Misc/Paths.h"
#include "Paths.h"

// Sets default values for this component's properties
UZISQLiteComponent::UZISQLiteComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UZISQLiteComponent::BeginPlay()
{
	Super::BeginPlay();
	CreateDataBase();
	// ...
}

int UZISQLiteComponent::callback(void * data, int argc, char ** argv, char ** Colname)
{
	for (int i = 0; i < argc; i++)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s = %s"), *FString(UTF8_TO_TCHAR(Colname[i])), *FString(UTF8_TO_TCHAR(argv[i])));
	}
	return 0;
}


// Called every frame
void UZISQLiteComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FString UZISQLiteComponent::returnString()
{
	return FString("Lazarev loh");
}

void UZISQLiteComponent::CreateDataBase()
{
	path = FPaths::ConvertRelativePathToFull(FPaths::GameDir()) + "Results.db";
	rc = sqlite3_open(StringCast<ANSICHAR>(*path).Get(), &dataBase);
	const char *data = "Callback execute";
	char *errMessage = 0;
	char *sql = "CREATE TABLE Answers(Represent TEXT, Based TEXT, Work TEXT, Passionate TEXT, Interesting TEXT)";
	if (rc)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(UTF8_TO_TCHAR(errMessage)));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DataBase opened Sucessfully!"));
	}

	rc = sqlite3_exec(dataBase, sql, callback, (void*)data, &errMessage);
	if (rc != SQLITE_OK)
	{
		UE_LOG(LogTemp, Warning, TEXT("SQL_ERROR %s"), *FString(UTF8_TO_TCHAR(errMessage)));
		sqlite3_free(errMessage);
		sqlite3_close(dataBase);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Table created sucsessfuly!"));
	}

	sqlite3_close(dataBase);
}

bool UZISQLiteComponent::InsertData(FString Query)
{
	const char *data = "Callback execute";
	char *errMessage = 0;
	rc = sqlite3_open(StringCast<ANSICHAR>(*path).Get(), &dataBase);
	auto sql = StringCast<ANSICHAR>(*Query);
	//ANSICHAR* queryAsUtf8 = TCHAR_TO_UTF8(*Query);
	rc = sqlite3_exec(dataBase, sql.Get(), callback, (void*)data, &errMessage);
	//UE_LOG(LogTemp, Warning, TEXT("SQL == %s"), *FString(sql.Get()));
	//UE_LOG(LogTemp, Warning, TEXT("FSTRING == %s"), *Query);
	if (rc != SQLITE_OK)
	{
		UE_LOG(LogTemp, Warning, TEXT("SQL_ERROR %s"), *FString(UTF8_TO_TCHAR(errMessage)));
		sqlite3_free(errMessage);
		sqlite3_close(dataBase);
		return false;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Data inserted sucsessfuly!"));
		return true;
	}
	sqlite3_close(dataBase);
}

FString UZISQLiteComponent::Query(FString query, int32 columnNumber)
{
	rc = sqlite3_open(StringCast<ANSICHAR>(*path).Get(), &dataBase);
	sqlite3_stmt *stmt;
	const char *tail;
	char *errMessage = 0;
	FString result;
	//ANSICHAR* queryAsUTF8 = TCHAR_TO_UTF8(*query);
	auto sql = StringCast<ANSICHAR>(*query);
	rc = sqlite3_prepare_v2(dataBase, sql.Get(), -1, &stmt, &tail);
	if (rc)
	{
		UE_LOG(LogTemp, Warning, TEXT("SQL_ERROR %s"), *FString(UTF8_TO_TCHAR(errMessage)));
		sqlite3_free(errMessage);
		sqlite3_close(dataBase);
		return FString("Error");
	}
	int rec_count = 0;
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		UE_LOG(LogTemp, Warning, TEXT("SQL_OUT %s"), *FString(UTF8_TO_TCHAR(sqlite3_column_text(stmt, columnNumber))));
		result = FString(UTF8_TO_TCHAR(sqlite3_column_text(stmt, columnNumber)));
	}
	return result;
	sqlite3_finalize(stmt);
	sqlite3_close(dataBase);
}















