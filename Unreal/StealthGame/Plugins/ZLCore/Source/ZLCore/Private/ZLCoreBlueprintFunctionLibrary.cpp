#include "ZLCoreBlueprintFunctionLibrary.h"
#include "ZLCore.h"
#include "ZLCallbackHandler.h"
#include "Misc/CommandLine.h"

UZLCallbackHandler* UZLCoreBlueprintFunctionLibrary::GetCallbackHandler()
{
 	auto& CoreModule = FModuleManager::GetModuleChecked<FZLCoreModule>(TEXT("ZLCore"));

	if (CoreModule.CallbackHandler == nullptr)
	{
		CoreModule.CallbackHandler = NewObject<UZLCallbackHandler>();
		CoreModule.CallbackHandler->AddToRoot(); //Stop GC
	} 

	return CoreModule.CallbackHandler;
}

void UZLCoreBlueprintFunctionLibrary::AssignClientProfile(const FString& clientIp, int newProfileId)
{
	auto& CoreModule = FModuleManager::GetModuleChecked<FZLCoreModule>(TEXT("ZLCore"));

	CoreModule.AssignClientProfile(clientIp, newProfileId);
}

void UZLCoreBlueprintFunctionLibrary::UnassignClientProfile(const FString& clientIp)
{
	auto& CoreModule = FModuleManager::GetModuleChecked<FZLCoreModule>(TEXT("ZLCore"));

	CoreModule.UnassignClientProfile(clientIp);
}

FZLSpaceCalibration UZLCoreBlueprintFunctionLibrary::GetGameSpaceCalibration()
{
	auto& CoreModule = FModuleManager::GetModuleChecked<FZLCoreModule>(TEXT("ZLCore"));
	return CoreModule.GetGameSpaceCalibration();
}

FZLSession UZLCoreBlueprintFunctionLibrary::GetSession()
{
	auto& CoreModule = FModuleManager::GetModuleChecked<FZLCoreModule>(TEXT("ZLCore"));
	return CoreModule.GetSession();
}

EZLGameState UZLCoreBlueprintFunctionLibrary::GetGameState()
{
	auto& CoreModule = FModuleManager::GetModuleChecked<FZLCoreModule>(TEXT("ZLCore"));
	return CoreModule.GetGameState();
}

FZLGameMasterView UZLCoreBlueprintFunctionLibrary::GetGameMasterView()
{
	auto& CoreModule = FModuleManager::GetModuleChecked<FZLCoreModule>(TEXT("ZLCore"));
	return CoreModule.GetGameMasterView();
}

FZLPlayerProfileMaps UZLCoreBlueprintFunctionLibrary::GetPlayerProfileMaps()
{
	auto& CoreModule = FModuleManager::GetModuleChecked<FZLCoreModule>(TEXT("ZLCore"));
	return CoreModule.GetPlayerProfileMaps();
}

FZLSite UZLCoreBlueprintFunctionLibrary::GetSiteInfo()
{
	auto& CoreModule = FModuleManager::GetModuleChecked<FZLCoreModule>(TEXT("ZLCore"));
	return CoreModule.GetSiteInfo();
}

FZLBackpackStatus UZLCoreBlueprintFunctionLibrary::GetBackpackStatus()
{
	auto& CoreModule = FModuleManager::GetModuleChecked<FZLCoreModule>(TEXT("ZLCore"));
	return CoreModule.GetBackpackStatus();
}

FZLLauncherInfo UZLCoreBlueprintFunctionLibrary::GetLauncherInfo()
{
	auto& CoreModule = FModuleManager::GetModuleChecked<FZLCoreModule>(TEXT("ZLCore"));
	return CoreModule.GetLauncherInfo();
}

FVector2D UZLCoreBlueprintFunctionLibrary::GetContentDimensions()
{
	auto& CoreModule = FModuleManager::GetModuleChecked<FZLCoreModule>(TEXT("ZLCore"));
	return CoreModule.GetContentDimensions();
}

void UZLCoreBlueprintFunctionLibrary::SetGameState(EZLGameState newState)
{
	auto& CoreModule = FModuleManager::GetModuleChecked<FZLCoreModule>(TEXT("ZLCore"));
	return CoreModule.SetGameState(newState);
}

void UZLCoreBlueprintFunctionLibrary::EndGame()
{
	auto& CoreModule = FModuleManager::GetModuleChecked<FZLCoreModule>(TEXT("ZLCore"));
	return CoreModule.EndGame();
}

void UZLCoreBlueprintFunctionLibrary::SetPlayerStats(FZLPlayerStatsMap newStats)
{
	auto& CoreModule = FModuleManager::GetModuleChecked<FZLCoreModule>(TEXT("ZLCore"));
	CoreModule.SetPlayerStats(newStats);
}

void UZLCoreBlueprintFunctionLibrary::SetPlayerScore(FString clientIpAddress, int score)
{
	auto& CoreModule = FModuleManager::GetModuleChecked<FZLCoreModule>(TEXT("ZLCore"));
	CoreModule.SetPlayerScore(clientIpAddress, score);
}

void UZLCoreBlueprintFunctionLibrary::SetPlayerStat(FString clientIpAddress, FString areaId, FString statId, float value)
{
	auto& CoreModule = FModuleManager::GetModuleChecked<FZLCoreModule>(TEXT("ZLCore"));
	CoreModule.SetPlayerStat(clientIpAddress, areaId, statId, value);
}

int UZLCoreBlueprintFunctionLibrary::GetPlayerScore(FString clientIpAddress)
{
	auto& CoreModule = FModuleManager::GetModuleChecked<FZLCoreModule>(TEXT("ZLCore"));
	return CoreModule.GetPlayerScore(clientIpAddress);
}

float UZLCoreBlueprintFunctionLibrary::GetPlayerStat(FString clientIpAddress, FString areaId, FString statId)
{
	auto& CoreModule = FModuleManager::GetModuleChecked<FZLCoreModule>(TEXT("ZLCore"));
	return CoreModule.GetPlayerStat(clientIpAddress, areaId, statId);
}

void UZLCoreBlueprintFunctionLibrary::SetContentDimensions(FVector2D dimensions)
{
	auto& CoreModule = FModuleManager::GetModuleChecked<FZLCoreModule>(TEXT("ZLCore"));
	CoreModule.SetContentDimensions(dimensions);
}

void UZLCoreBlueprintFunctionLibrary::SetPlayerTrackingUpdate(FZLPlayerTrackingData trackingData)
{
	auto& CoreModule = FModuleManager::GetModuleChecked<FZLCoreModule>(TEXT("ZLCore"));
	CoreModule.SetPlayerTrackingData(trackingData);
}


ELauncherMode UZLCoreBlueprintFunctionLibrary::GetLauncherMode()
{
	ELauncherMode launcherMode = UZLCoreBlueprintFunctionLibrary::GetLauncherInfo().Mode;

	// Override the mode if command line parameter is specified
	FString mode;		
	if (FParse::Value(FCommandLine::Get(), TEXT("mode"), mode)) {
		mode = mode.Replace(TEXT("="), TEXT(""));

		if (mode.Equals(TEXT("spectator"), ESearchCase::IgnoreCase))
		{
			return ELauncherMode::SPECTATOR;
		}

		if (mode.Equals(TEXT("client"), ESearchCase::IgnoreCase))
		{
			return ELauncherMode::BACKPACK;
		}

		if (mode.Equals(TEXT("gamemaster"), ESearchCase::IgnoreCase))
		{
			return ELauncherMode::GAME_MASTER;
		}

		if (mode.Equals(TEXT("server"), ESearchCase::IgnoreCase))
		{
			return ELauncherMode::SERVER;
		}
	}

	return launcherMode;
}

FVector UZLCoreBlueprintFunctionLibrary::SpaceMatrixTransformPosition(FMatrix spaceMatrix, FVector value) {
	// the space matrices uses the 3rd component of the vector to represent whether it is a position or a vector and should be translated, just like FMatrix adds a fourth component for TransformPosition and TransformVector.
	// therefore, we set Z = 1.0f, to have the position be translated by the matrix and then set the final vector with the original Z value.
	return FVector(FVector2D(spaceMatrix.TransformVector(FVector(value.X, value.Y, 1.0f))), value.Z);
}