// Fill out your copyright notice in the Description page of Project Settings.

#include "ZLTelemetry.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/Core/Public/HAL/FileManager.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"

ZLTelemetry::ZLTelemetry(FString path)
{
	LogPath = path;
}

ZLTelemetry::~ZLTelemetry()
{
}

void ZLTelemetry::LogEvent(const UStruct* StructDefinition, const void* Struct)
{
	FString InnerString;
	FString now = FDateTime::UtcNow().ToIso8601();

	FString typeName = StructDefinition->GetFName().ToString();

	FJsonObjectConverter::UStructToJsonObjectString(StructDefinition, Struct, InnerString, 0, 0, 0, nullptr, false);

	// Encapsulate inStruct in object named by the class name and add timestamp to the root
	FString jsonString = FString::Printf(TEXT("{\"@t\":\"%s\",\"%s\":%s,\"@type\":\"%s\"}"), *now, *typeName, *InnerString, *typeName);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *jsonString);
	AppendLineToLog(jsonString);
}

void ZLTelemetry::AppendLineToLog(FString line)
{
	if (CurrentFilePath.IsEmpty())
	{
		InitializeNewLogFile();

	}

	FFileHelper::SaveStringToFile(line + TEXT("\r\n"),
		*LogPath, FFileHelper::EEncodingOptions::ForceAnsi,
		&IFileManager::Get(),
		EFileWrite::FILEWRITE_Append);
}

void ZLTelemetry::InitializeNewLogFile()
{
	// We don't have a log file assigned yet. 
	FString path;
	FString filename;
	FString extension;

	FPaths::Split(this->LogPath, path, filename, extension);

	FDateTime now = FDateTime::Now();	
	filename.Append("_" + now.ToString((TEXT("%Y%m%d-%H%M%S"))));

	//create directory if it doesn't exist
	IFileManager::Get().MakeDirectory(*path, true);

	LogPath = path + "\\"+filename +"." + extension;

	UE_LOG(LogTemp, Log, TEXT("new telemetry log: %s"), *LogPath);

}
