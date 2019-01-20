// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "TestActor.generated.h"



USTRUCT()
struct FTelemetryEvent
{
	GENERATED_BODY()
public:
	
	UPROPERTY()
	int32 version = 1000;
};

USTRUCT()
struct FPerson : public FTelemetryEvent
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FString Name;

	UPROPERTY()
	FString occupation;

	UPROPERTY()
	int32 Age;

	UPROPERTY()
	FVector pos;

	UPROPERTY()
	FRotator rot;
};




UCLASS()
class JSONTEST_API ATestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	template<typename InStructType>
	static void LogTelemetryEvent(const InStructType& InStruct);

	
	
};
