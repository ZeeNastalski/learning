// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "ZLGameViewportClient.generated.h"

namespace EZLSplitScreenType
{
	enum Type
	{
		//Single Player
		NoPlayers = ESplitScreenType::SplitTypeCount,
		OnePlayer,
		TwoPlayers,
		ThreePlayers,
		FourPlayers,
		FivePlayers,
		SixPlayers,
		SevenPlayers,
		EightPlayers
	};
}


/**
 *
 */
UCLASS()
class ZLCORE_API UZLGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()

public:
	UZLGameViewportClient(const FObjectInitializer & ObjectInitializer);
	virtual void UpdateActiveSplitscreenType() override;
	virtual void LayoutPlayers() override;

	APlayerController * CreatePlayer(const UObject * WorldContextObject, int32 ControllerId, bool bSpawnPawn);
	
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY() 
	TMap<uint32, APlayerController*> LocalPlayerMap;

	APawn* PawnForPlayerId(int32 id);
	FString ModeString();
};