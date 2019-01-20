// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ZLTelemetry.generated.h"

/**
 * 
 */
UCLASS()
class JSONTEST_API UZLTelemetry : public UObject
{
	GENERATED_BODY()

public:	

	
	static void LogTelemetryEvent(const UStruct* StructDefinition, const void* Struct);

	template<typename InStructType>
	static void LogTelemetryEvent(const InStructType& InStruct) 
	{
		LogTelemetryEvent(InStructType::StaticStruct(), &InStruct);
	}
};
