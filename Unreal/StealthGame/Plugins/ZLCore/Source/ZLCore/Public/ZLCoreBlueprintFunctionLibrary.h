#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "ZLCallbackHandler.h"
#include "ZLStructs.h"

#include "ZLCoreBlueprintFunctionLibrary.generated.h"

UCLASS()
class ZLCORE_API UZLCoreBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	static ELauncherMode ModeOverride;

	UFUNCTION(BlueprintPure, Category = ZeroLatency)
	static UZLCallbackHandler* GetCallbackHandler();

	UFUNCTION(BlueprintPure, Category = ZeroLatency)
	static FZLSpaceCalibration GetGameSpaceCalibration();

	UFUNCTION(BlueprintPure, Category = ZeroLatency)
	static FZLSession GetSession();

	UFUNCTION(BlueprintPure, Category = ZeroLatency)
	static EZLGameState GetGameState();

	UFUNCTION(BlueprintPure, Category = ZeroLatency)
	static FZLGameMasterView GetGameMasterView();

	UFUNCTION(BlueprintPure, Category = ZeroLatency)
	static FZLPlayerProfileMaps GetPlayerProfileMaps();
	
	UFUNCTION(BlueprintPure, Category = ZeroLatency)
	static FZLSite GetSiteInfo();

	UFUNCTION(BlueprintPure, Category = ZeroLatency)
	static FZLBackpackStatus GetBackpackStatus();

	UFUNCTION(BlueprintPure, Category = ZeroLatency)
	static FZLLauncherInfo GetLauncherInfo();

	UFUNCTION(BlueprintPure, Category = ZeroLatency)
	static ELauncherMode GetLauncherMode();

	UFUNCTION(BlueprintPure, Category = ZeroLatency)
	static FVector2D GetContentDimensions();

	UFUNCTION(BlueprintCallable, Category = ZeroLatency)
	static void AssignClientProfile(const FString& clientIp, int newProfileId);

	UFUNCTION(BlueprintCallable, Category = ZeroLatency)
	static void UnassignClientProfile(const FString& clientIp);

	UFUNCTION(BlueprintCallable, Category = ZeroLatency)
	static void SetGameState(EZLGameState newState);

	UFUNCTION(BlueprintCallable, Category = ZeroLatency)
	static void EndGame();

	UFUNCTION(BlueprintCallable, Category = ZeroLatency)
	static void SetPlayerStats(FZLPlayerStatsMap newStats);

	UFUNCTION(BlueprintCallable, Category = ZeroLatency)
	static void SetPlayerScore(FString clientIpAddress, int score);

	UFUNCTION(BlueprintCallable, Category = ZeroLatency)
	static void SetPlayerStat(FString clientIpAddress, FString areaId, FString statId, float value);

	UFUNCTION(BlueprintCallable, Category = ZeroLatency)
	static int GetPlayerScore(FString clientIpAddress);

	UFUNCTION(BlueprintCallable, Category = ZeroLatency)
	static float GetPlayerStat(FString clientIpAddress, FString areaId, FString statId);

	UFUNCTION(BlueprintCallable, Category = ZeroLatency)
	static void SetContentDimensions(FVector2D dimensions);

	UFUNCTION(BlueprintCallable, Category = ZeroLatency)
	static void OverrideLauncherMode(ELauncherMode mode);

	static void SetPlayerTrackingUpdate(FZLPlayerTrackingData playerInfo);

	// translate the vector such that the X and Y components are transformed, and the Z component remains the same.
	static FVector SpaceMatrixTransformPosition(FMatrix spaceMatrix, FVector value);

	
};
