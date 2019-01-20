// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class JSONTEST_API ZLTelemetry
{
public:
	ZLTelemetry();
	~ZLTelemetry();

	void LogEvent(const UStruct* StructDefinition, const void* Struct);

	template<typename InStructType>
	void LogEvent(const InStructType& InStruct)
	{
		LogEvent(InStructType::StaticStruct(), &InStruct);
	}
};
