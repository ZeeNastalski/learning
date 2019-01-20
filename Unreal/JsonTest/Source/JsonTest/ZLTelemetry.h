// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class JSONTEST_API ZLTelemetry
{
public:
	ZLTelemetry(FString LogPath = "c:\\ZeroLatency\\Logging\\unrealgame.json");
	~ZLTelemetry();


	FString LogPath;
	FString CurrentFilePath;

	void LogEvent(const UStruct* StructDefinition, const void* Struct);

	template<typename InStructType>
	void LogEvent(const InStructType& InStruct)
	{
		LogEvent(InStructType::StaticStruct(), &InStruct);
	}

protected:
	void AppendLineToLog(FString line);
	void InitializeNewLogFile();
};
