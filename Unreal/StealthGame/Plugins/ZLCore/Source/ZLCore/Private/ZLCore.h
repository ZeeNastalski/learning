#pragma once

#include "Modules/ModuleManager.h"
#include "Tickable.h"

#include "ZLCoreBlueprintFunctionLibrary.h"

class APlayerController;
class UZLCallbackHandler;
class UWorld;

enum class EZLGameState : uint8;
struct FZLSession;
struct FZLGameMasterView;
struct FZLPlayerProfileMaps;
struct FZLPlayerStatsMap;

DECLARE_LOG_CATEGORY_EXTERN(LogZeroLatencyCore, Log, All);

class FZLCoreModule : public IModuleInterface, public FTickableGameObject
{	
	/** IModuleInterface implementation */
	void StartupModule() override;
	void ShutdownModule() override;
	/**/

	/** FTickableGameObject implementation */
	bool IsTickableWhenPaused() const override;

	bool IsTickableInEditor() const override;

	void Tick(float DeltaTime) override;

	TStatId GetStatId() const override;

public:
	UWorld* GetTickableGameObjectWorld() const override;
	/**/
	
	/** ZL */
	void AssignClientProfile(const FString& clientIp, int newProfileId);
	void UnassignClientProfile(const FString& clientIp);

	void SetGameState(EZLGameState newState);
	void EndGame();

	void SetPlayerStats(FZLPlayerStatsMap newStats);
	void SetPlayerScore(FString clientIpAddress, long score);
	void SetPlayerStat(FString clientIpAddress, FString areaId, FString statId, double value);
	void SetPlayerTrackingData(FZLPlayerTrackingData trackingData);
	long GetPlayerScore(FString clientIpAddress);
	double GetPlayerStat(FString clientIpAddress, FString areaId, FString statId);

	inline void SetContentDimensions(FVector2D newContentDimensions) { ContentDimensions = newContentDimensions; }

private:
	void StartZLIPC();
	void StopZLIPC();

	void OnDebugStateDumpCommand();

public:
	UZLCallbackHandler* CallbackHandler = nullptr;

	FZLSpaceCalibration GetGameSpaceCalibration();
	EZLGameState GetGameState();
	FZLSession GetSession();
	FZLPlayerProfileMaps GetPlayerProfileMaps();
	FZLGameMasterView GetGameMasterView();
	FZLSite GetSiteInfo();
	FZLBackpackStatus GetBackpackStatus();
	FZLLauncherInfo GetLauncherInfo();
	
	inline FVector2D GetContentDimensions() { return ContentDimensions; }

private:
	FDelegateHandle OnPostWorldInitHandle;

	UWorld* GameWorld = nullptr;

	void* IPCDllHandle = nullptr;

	bool bRunning = false;

	class FAutoConsoleCommand* DebugStateDumpCommand;
	
	FZLPlayerStatsMap* PlayerStatsMap;

	FVector2D ContentDimensions = FVector2D(0.0f, 0.0f);

	static TMap<EContentMap, FZLMapBounds> ContentMapBounds;
};