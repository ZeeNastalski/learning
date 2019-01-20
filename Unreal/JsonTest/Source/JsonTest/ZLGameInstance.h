// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ZLTelemetry.h"
#include "ZLGameInstance.generated.h"



/**
 * 
 */
UCLASS()
class JSONTEST_API UZLGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	ZLTelemetry Telemetry;
		
};
