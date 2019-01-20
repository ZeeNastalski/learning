// Fill out your copyright notice in the Description page of Project Settings.

#include "ZLTelemetry.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"



void UZLTelemetry::LogTelemetryEvent(const UStruct* StructDefinition, const void* Struct)
{
	FString InnerString;
	FString now = FDateTime::UtcNow().ToIso8601();

	FName typeName = StructDefinition->GetFName();

	FJsonObjectConverter::UStructToJsonObjectString(StructDefinition, Struct, InnerString, 0, 0, 0, nullptr, false);

	// Encapsulate inStruct in object named by the class name and add timestamp to the root
	FString jsonString = FString::Printf(TEXT("{\"@t\":\"%s\",\"%s\":%s}"), *now, *(typeName.ToString()), *InnerString);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *jsonString);
}
