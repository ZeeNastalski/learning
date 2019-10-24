// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ZLCore.h"
#include "ZeroLatencyAPI.h"
#include "ZLCallbackHandler.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Engine/NetConnection.h"
#include "UnrealEngine.h"
#include "ZLIPCConnectionHandle.h"
#include "ELoggingLevel.h"
#include "ZLStructParser.h"
#include "ZLProtoParser.h"
#include "ZLConsoleCommands.h"

#pragma warning(push)
#pragma warning(disable : 4647)
#pragma warning(disable : 4668)
#include "proto/controller/Input.pb.h"
#include "proto/player/Stats.pb.h"
#include "proto/GameSpaceCalibration.pb.h"
#include "proto/GameState.pb.h"
#include "proto/Session.pb.h"
#include "proto/Site.pb.h"
#include "proto/GameMasterView.pb.h"
#include "proto/Networking/Transmission.pb.h"
#include "proto/ProfileMaps.pb.h"
#include "proto/Site.pb.h"
#include "proto/GameResults.pb.h"
#include "proto/launcher/LauncherInfo.pb.h"
#pragma warning(pop)

#include <Engine/GameEngine.h>
#include <Engine/LocalPlayer.h>
#include <Engine/Console.h>
#include <Kismet/GameplayStatics.h>

#define LOCTEXT_NAMESPACE "FZLCoreModule"

DEFINE_LOG_CATEGORY(LogZeroLatencyCore);

using namespace zl;

FZLCoreModule* CoreModule = nullptr;

TMap<EContentMap, FZLMapBounds> FZLCoreModule::ContentMapBounds = TMap<EContentMap, FZLMapBounds>{
	TPair<EContentMap, FZLMapBounds> {
		EContentMap::SteelStreet,
		// Actually the L-shaped 30x15, but only OB1 supports that.
		// should revisit this ...
		FZLMapBounds(
			TArray<FVector2D>{
				FVector2D{0.0f,20.0f},
				FVector2D{9.6f,20.0f},
				FVector2D{9.6f,0.0f},
				FVector2D{0.0f,0.0f}
			},
			TArray<FZLObstacleBounds>{})
	},
	TPair<EContentMap, FZLMapBounds> {
	EContentMap::Orlando,
	FZLMapBounds(
		TArray<FVector2D>{
			FVector2D{0.0f,0.0f},
			FVector2D{0.0f,18.75f},
			FVector2D{10.0f,18.75f},
			FVector2D{10.0f,0.0f}
		},
		TArray<FZLObstacleBounds>{
			FZLObstacleBounds(TArray<FVector2D>{
				FVector2D{1.189f,11.371f},
				FVector2D{1.189f,11.917f},
				FVector2D{1.9f,11.917f},
				FVector2D{1.9f,11.371f}
			}),
			FZLObstacleBounds(TArray<FVector2D>{
				FVector2D{8.1f,11.092f},
				FVector2D{8.1f,11.917f},
				FVector2D{8.9f,11.917f},
				FVector2D{8.9f,11.092f}
			})
		})
	},
	TPair<EContentMap, FZLMapBounds> {
	EContentMap::KalahariPoconos,
	FZLMapBounds(
		TArray<FVector2D>{
			FVector2D{8.098f,4.165f},
			FVector2D{8.098f,0.0f},
			FVector2D{0.0f,0.0f},
			FVector2D{0.0f,15.0f},
			FVector2D{14.741f,15.0f},
			FVector2D{14.741f,11.725f},
			FVector2D{15.0f,11.725f},
			FVector2D{15.0f,0.0f},
			FVector2D{8.545f,0.0f},
			FVector2D{8.545f,4.165f}
		},
		TArray<FZLObstacleBounds>{
			FZLObstacleBounds(TArray<FVector2D>{
				FVector2D{7.96f,10.982f},
				FVector2D{8.34f,10.982f},
				FVector2D{8.34f,10.473f},
				FVector2D{7.96f,10.473f}
			})
		})
	},
	TPair<EContentMap, FZLMapBounds> {
	EContentMap::KalahariDells,
	FZLMapBounds(
		TArray<FVector2D>{
			FVector2D{0.0f,20.0f},
			FVector2D{10.0f,20.0f},
			FVector2D{10.0f,0.0f},
			FVector2D{0.0f,0.0f}
		},
		TArray<FZLObstacleBounds>{
			FZLObstacleBounds(TArray<FVector2D>{
				FVector2D{6.595f,16.44f},
				FVector2D{6.595f,16.595f},
				FVector2D{6.75f,16.595f},
				FVector2D{6.75f,16.44f}
			}),
			FZLObstacleBounds(TArray<FVector2D>{
				FVector2D{6.595f,8.134f},
				FVector2D{6.595f,8.289f},
				FVector2D{6.75f,8.289f},
				FVector2D{6.75f,8.134f}
			})
		})
	},
	TPair<EContentMap, FZLMapBounds> {
	EContentMap::Rectangle20x9p6,
	FZLMapBounds(
		TArray<FVector2D>{
			FVector2D{0.0f,20.0f},
			FVector2D{9.6f,20.0f},
			FVector2D{9.6f,0.0f},
			FVector2D{0.0f,0.0f}
		},
		TArray<FZLObstacleBounds>{})
	},
	TPair<EContentMap, FZLMapBounds> {
	EContentMap::Square15x15NoPillar,
	FZLMapBounds(
		TArray<FVector2D>{
			FVector2D{0.0f,0.0f},
			FVector2D{0.0f,15.0f},
			FVector2D{15.0f,15.0f},
			FVector2D{15.0f,0.0f}
		},
		TArray<FZLObstacleBounds>{})
	},
	TPair<EContentMap, FZLMapBounds> {
	EContentMap::Tongyeong,
	FZLMapBounds(
		TArray<FVector2D>{
			FVector2D{0.0f,0.0f},
			FVector2D{0.0f,10.14f},
			FVector2D{10.09f,10.14f},
			FVector2D{10.09f,0.0f}
		},
		TArray<FZLObstacleBounds>{
			FZLObstacleBounds(TArray<FVector2D>{
				FVector2D{5.0f,5.7f},
				FVector2D{5.0f,5.14f},
				FVector2D{4.44f,5.14f},
				FVector2D{4.44f,5.7f}
			})
		})
	}
};

void OnControllerInputChanged(const proto::controller::Input& packet)
{
	if (!CoreModule || !CoreModule->CallbackHandler || !CoreModule->CallbackHandler->OnBlasterInputUpdated.IsBound())
	{
		return;
	}

	CoreModule->CallbackHandler->OnBlasterInputUpdated.Broadcast(zl::ToStruct(packet));
}


void OnGameSpaceCalibrationChanged(const proto::GameSpaceCalibration& packet)
{
	if (!CoreModule || !CoreModule->CallbackHandler || !CoreModule->CallbackHandler->OnGamespaceCalibrationUpdated.IsBound())
	{
		return;
	}

	CoreModule->CallbackHandler->OnGamespaceCalibrationUpdated.Broadcast(packet.m11(), packet.m21(), packet.m31(), packet.m12(), packet.m22(), packet.m32());
}

void OnGameStateChanged(const proto::GameState& packet)
{
	if (!CoreModule || !CoreModule->CallbackHandler || !CoreModule->CallbackHandler->OnGameStateUpdated.IsBound())
	{
		return;
	}

	CoreModule->CallbackHandler->OnGameStateUpdated.Broadcast(zl::ToStruct(packet));
}

void OnSessionChanged(const proto::Session& packet)
{
	if (!CoreModule || !CoreModule->CallbackHandler || !CoreModule->CallbackHandler->OnSessionUpdated.IsBound())
	{
		return;
	}

	CoreModule->CallbackHandler->OnSessionUpdated.Broadcast(zl::ToStruct(packet));
}

void OnSiteInfoChanged(const proto::Site& packet)
{
	if (!CoreModule || !CoreModule->CallbackHandler || !CoreModule->CallbackHandler->OnSiteInfoUpdated.IsBound())
	{
		return;
	}

	CoreModule->CallbackHandler->OnSiteInfoUpdated.Broadcast(zl::ToStruct(packet));
}

void OnGameMasterViewChanged(const proto::GameMasterView& packet)
{
	if (!CoreModule || !CoreModule->CallbackHandler || !CoreModule->CallbackHandler->OnGameMasterViewUpdated.IsBound())
	{
		return;
	}

	CoreModule->CallbackHandler->OnGameMasterViewUpdated.Broadcast(zl::ToStruct(packet));
}

void OnPlayerProfileMapsChanged(const proto::ProfileMaps& packet)
{
	if (!CoreModule || !CoreModule->CallbackHandler || !CoreModule->CallbackHandler->OnPlayerProfileMapsUpdated.IsBound())
	{
		return;
	}

	CoreModule->CallbackHandler->OnPlayerProfileMapsUpdated.Broadcast(zl::ToStruct(packet));
}

void OnLauncherInfoChanged(const proto::launcher::LauncherInfo &packet)
{
	if (!CoreModule || !CoreModule->CallbackHandler || !CoreModule->CallbackHandler->OnLauncherInfoUpdated.IsBound())
	{
		return;
	}

	CoreModule->CallbackHandler->OnLauncherInfoUpdated.Broadcast(zl::ToStruct(packet));
}

void FZLCoreModule::StartupModule()
{
	UE_LOG(LogZeroLatencyCore, Log, TEXT("Searching for ZeroLatencyIPC.dll directory."));

	CoreModule = this;

#if DEBUG_ZLAPI
	const auto ZLAPIDllSubdir = TEXT("Plugins/ZLCore/ZLAPI/Debug");
#else
	const auto ZLAPIDllSubdir = TEXT("Plugins/ZLCore/ZLAPI/Release");
#endif

	//TODO: Improve dll searching. Should check all subdirectories of plugins for zlcore.
	//Game/source first
	auto CppAPIDirectory = FPaths::ProjectDir() / ZLAPIDllSubdir;

	FPlatformProcess::PushDllDirectory(*CppAPIDirectory);
	IPCDllHandle = FPlatformProcess::GetDllHandle(*(CppAPIDirectory / TEXT("ZeroLatencyIPC.dll")));
	FPlatformProcess::PopDllDirectory(*CppAPIDirectory);

	if (IPCDllHandle == nullptr)
	{
		CppAPIDirectory = FPaths::EngineDir() / ZLAPIDllSubdir;

		FPlatformProcess::PushDllDirectory(*CppAPIDirectory);
		IPCDllHandle = FPlatformProcess::GetDllHandle(*(CppAPIDirectory / TEXT("ZeroLatencyIPC.dll")));
		FPlatformProcess::PopDllDirectory(*CppAPIDirectory);
	}

	if (IPCDllHandle == nullptr)
	{
		UE_LOG(LogZeroLatencyCore, Warning, TEXT("Could not locate ZeroLatencyAPI.dll!"));
		return;
	}
	else
	{
		UE_LOG(LogZeroLatencyCore, Log, TEXT("Found ZeroLatencyAPI.dll at %s"), *CppAPIDirectory);
	}

	// Use a lambda over instead of a member method here because the signature includes the UWorld::InitializationValues parameter. This would require an Engine/World.h include in our header which would increase compile times.
	OnPostWorldInitHandle = FWorldDelegates::OnPostWorldInitialization.AddLambda([this](UWorld* World, const UWorld::InitializationValues IVS)
	{
		if (!World || !World->IsGameWorld())
		{
			return;
		}

		GameWorld = World;
	});
}

void FZLCoreModule::ShutdownModule()
{
	UE_LOG(LogZeroLatencyCore, Log, TEXT("Shutting down module."));

	CoreModule = nullptr;

	StopZLIPC();

	if (CallbackHandler != nullptr)
	{
		// This object may not be valid during at certain times
		if (CallbackHandler->IsValidLowLevel() && CallbackHandler->IsRooted())
		{
			CallbackHandler->RemoveFromRoot();
		}

		CallbackHandler = nullptr;
	}

	if (OnPostWorldInitHandle.IsValid())
	{
		FWorldDelegates::OnPreWorldInitialization.Remove(OnPostWorldInitHandle);
	}
}

bool FZLCoreModule::IsTickableWhenPaused() const
{
	return true;
}

bool FZLCoreModule::IsTickableInEditor() const
{
	// Ticking in the editor causes the game to connect to the launcher during development.
	return false;
}

void FZLCoreModule::Tick(float DeltaTime)
{
	if (!GameWorld)
	{
		return;
	}

	if (!bRunning)
	{
		auto GI = GameWorld->GetGameInstance();
		if (!GI)
		{
			return;
		}

		auto RefCtr = NewObject<UZLIPCConnectionHandle>();
		RefCtr->OnHandleClosed.AddRaw(this, &FZLCoreModule::StopZLIPC);
		GI->RegisterReferencedObject(RefCtr);

		StartZLIPC();
	}

	zl::Tick((1.0f / DeltaTime)); //TODO: pass in heart beat data here, fps etc
}

TStatId FZLCoreModule::GetStatId() const
{
	return TStatId();
}

UWorld* FZLCoreModule::GetTickableGameObjectWorld() const
{
	return GameWorld;
}

void FZLCoreModule::AssignClientProfile(const FString& clientIp, int newProfileId)
{
	zl::AssignClientProfile(TCHAR_TO_ANSI(*clientIp), newProfileId);
}

void FZLCoreModule::UnassignClientProfile(const FString& clientIp)
{
	zl::UnassignClientProfile(TCHAR_TO_ANSI(*clientIp));
}

void FZLCoreModule::SetGameState(EZLGameState newState)
{
	zl::SetGameState(zl::ToProto(newState));
}

void FZLCoreModule::OnDebugStateDumpCommand()
{
	// Grabs a string of the internal debug state of the API
	char buffer[8192] = { 0 };
	zl::GetDebugStateDumpString(buffer, sizeof(buffer));

	FString fDebugDumpString(buffer);

	// Log to the viewport console (press tilde ~ twice to see)
	APlayerController* PC = (GameWorld ? UGameplayStatics::GetPlayerController(GameWorld, 0) : NULL);
	ULocalPlayer* LocalPlayer = (PC ? Cast<ULocalPlayer>(PC->Player) : NULL);
	if (LocalPlayer && LocalPlayer->ViewportClient && LocalPlayer->ViewportClient->ViewportConsole)
	{
		LocalPlayer->ViewportClient->ViewportConsole->OutputText(fDebugDumpString);
	}

	// Log to standard UE log
	UE_LOG(LogTemp, Log, TEXT("%s"), *fDebugDumpString);
}

void FZLCoreModule::EndGame()
{
	proto::GameResults gameResults;

	zl::EndGame(gameResults);
}

void FZLCoreModule::SetPlayerStats(FZLPlayerStatsMap newStats)
{
	zl::SetPlayerStats(zl::ToProto(newStats));

	// Make a clone and assign it to our local state (because keeping a reference would mean data could change without us calling UpdatePlayerStats)
	*PlayerStatsMap = zl::ToStruct(zl::ToProto(newStats));
}

void FZLCoreModule::SetPlayerScore(FString clientIpAddress, long score)
{
	if (PlayerStatsMap->PlayerStats.Contains(clientIpAddress))
	{
		PlayerStatsMap->PlayerStats[clientIpAddress].Score = score;
	}
	else
	{
		FZLPlayerStats playerStats;
		playerStats.Score = score;
		PlayerStatsMap->PlayerStats.Add(clientIpAddress, playerStats);
	}

	SetPlayerStats(*PlayerStatsMap);
}

void FZLCoreModule::SetPlayerStat(FString clientIpAddress, FString areaId, FString statId, double value)
{
	PlayerStatsMap->SetStat(clientIpAddress, areaId, statId, value);

	SetPlayerStats(*PlayerStatsMap);
}

void FZLCoreModule::SetPlayerTrackingData(FZLPlayerTrackingData trackingData)
{	
	zl::SetPlayerTrackingData(zl::ToProto(trackingData));
}

long FZLCoreModule::GetPlayerScore(FString clientIpAddress)
{
	if (PlayerStatsMap->PlayerStats.Contains(clientIpAddress))
	{
		return PlayerStatsMap->PlayerStats[clientIpAddress].Score;
	}

	return 0;
}

double FZLCoreModule::GetPlayerStat(FString clientIpAddress, FString areaId, FString statId)
{
	if (PlayerStatsMap->PlayerStats.Contains(clientIpAddress))
	{
		auto& playerStats = PlayerStatsMap->PlayerStats[clientIpAddress];
		
		if (playerStats.AreaStats.Contains(areaId))
		{
			auto& areaStats = playerStats.AreaStats[areaId];

			if (areaStats.Stats.Contains(statId))
			{
				return areaStats.Stats[statId];
			}
		}
	}

	return 0.0;
}

void FZLCoreModule::StartZLIPC()
{
	if (!bRunning)
	{
		zl::Start(zl::ELoggingLevel::kLoggingLevelVerbose);

		zl::SetControllerInputChangedCallback(&OnControllerInputChanged);
		zl::SetGameSpaceCalibrationChangedCallback(&OnGameSpaceCalibrationChanged);
		zl::SetGameStateChangedCallback(&OnGameStateChanged);
		zl::SetSessionChangedCallback(&OnSessionChanged);
		zl::SetSiteInfoChangedCallback(&OnSiteInfoChanged);
		zl::SetGameMasterViewChangedCallback(&OnGameMasterViewChanged);
		zl::SetPlayerProfileMapsChangedCallback(&OnPlayerProfileMapsChanged);
		zl::SetLauncherInfoChangedCallback(&OnLauncherInfoChanged);

		DebugStateDumpCommand = new FAutoConsoleCommand(
			TEXT("ZLDebugStateDump"),
			TEXT("Prints internal ZLCore state to the screen and output console. Used for development purposes."),
			FConsoleCommandDelegate::CreateRaw(this, &FZLCoreModule::OnDebugStateDumpCommand)
		);

		RegisterConsoleCommands();

		PlayerStatsMap = new FZLPlayerStatsMap();

		bRunning = true;
	}
}

void FZLCoreModule::StopZLIPC()
{
	if (bRunning)
	{
		zl::Stop();

		zl::SetControllerInputChangedCallback(nullptr);
		zl::SetGameSpaceCalibrationChangedCallback(nullptr);
		zl::SetGameStateChangedCallback(nullptr);
		zl::SetSessionChangedCallback(nullptr);
		zl::SetSiteInfoChangedCallback(nullptr);
		zl::SetGameMasterViewChangedCallback(nullptr);
		zl::SetPlayerProfileMapsChangedCallback(nullptr);
		zl::SetLauncherInfoChangedCallback(nullptr);

		DeregisterConsoleCommands();

		delete DebugStateDumpCommand;
		bRunning = false;

		GameWorld = nullptr;
	}
}

FMatrix FromTranslation(FVector2D translation)
{
	return FMatrix(FVector(1.0f, 0.0f, translation.X),
		FVector(0.0f, 1.0f, translation.Y),
		FVector(0.0f, 0.0f, 1.0f),
		FVector(0.0f, 0.0f, 0.0f));
}

FMatrix FromRotation(float rotation)
{
	return FMatrix(FVector(FMath::Cos(rotation), FMath::Sin(rotation), 0.0f),
		FVector(-FMath::Sin(rotation), FMath::Cos(rotation), 0.0f),
		FVector(0.0f, 0.0f, 1.0f),
		FVector(0.0f, 0.0f, 0.0f));
}

FMatrix FromScale(FVector2D scale)
{
	return FMatrix(FVector(scale.X, 0.0f, 0.0f),
		FVector(0.0f, scale.Y, 0.0f),
		FVector(0.0f, 0.0f, 1.0f),
		FVector(0.0f, 0.0f, 0.0f));
}

// find the original translation, rotation and scale of a matrix that is composed of a TRS.
// does not produce valid results for matrix that has shear or skew.
// warning: decomposition returns low-precision values. Do not expect these values to produce good quality results in general.
// returns tuple of translation, rotation (in radians), scale
TTuple<FVector2D, float, FVector2D> Decomposes3x3TRS(FMatrix mat) {
	// Extract new local position
	auto translation = FVector2D(mat.M[0][2], mat.M[1][2]);

	// Extract new local scale
	auto scale = FVector2D(
		mat.GetColumn(0).Size(),
		mat.GetColumn(1).Size()
	);

	// Extract new local rotation
	auto from = FVector2D(mat.M[0][1], mat.M[1][1]);
	from.Normalize();
	auto to = FVector2D(0.0f, 1.0f);
	auto rotation = FMath::Acos(FMath::Clamp(FVector2D::DotProduct(from, to), -1.0f, 1.0f)) * FMath::Sign(from.X * to.Y - from.Y * to.X);

	return TTuple<FVector2D, float, FVector2D>(translation, rotation, scale);
}


FZLSpaceCalibration FZLCoreModule::GetGameSpaceCalibration()
{
	auto switchComponents = [](FVector2D v) { return FVector2D(v.Y, v.X); };

	auto switchMatrix = [](FMatrix spaceMatrix) {
		FMatrix result = FMatrix::Identity;
		result.M[0][0] = spaceMatrix.M[1][1];
		result.M[1][0] = spaceMatrix.M[1][0];
		result.M[2][0] = spaceMatrix.M[1][2];
		result.M[0][1] = spaceMatrix.M[0][1];
		result.M[1][1] = spaceMatrix.M[0][0];
		result.M[2][1] = spaceMatrix.M[0][2];
		return result;
	};

	auto GamespaceCalibration = zl::GetGameSpaceCalibration();

	// The identity is used by our code with one access reversed
	auto trackingToPortalMatrix = FMatrix::Identity;

	// Transform from calibrator coordinate frame to unreal coordinate frame
	// ... still hasn't flipped the X and Y components appropriately, we do that with switchMatrix()
	trackingToPortalMatrix.M[0][0] = GamespaceCalibration.m11();
	trackingToPortalMatrix.M[0][1] = GamespaceCalibration.m21();
	trackingToPortalMatrix.M[0][2] = GamespaceCalibration.m31();
	trackingToPortalMatrix.M[1][0] = GamespaceCalibration.m12();
	trackingToPortalMatrix.M[1][1] = GamespaceCalibration.m22();
	trackingToPortalMatrix.M[1][2] = GamespaceCalibration.m32();

	// for the translation components, convert from Unity units (metres) to Unreal units (centimetres).
	trackingToPortalMatrix.M[0][2] *= 100.f;
	trackingToPortalMatrix.M[1][2] *= 100.f;

	if (trackingToPortalMatrix.M[0][0] == 0 &&
		trackingToPortalMatrix.M[0][1] == 0 &&
		trackingToPortalMatrix.M[0][2] == 0 &&
		trackingToPortalMatrix.M[1][0] == 0 &&
		trackingToPortalMatrix.M[1][1] == 0 &&
		trackingToPortalMatrix.M[1][2] == 0)
	{
		trackingToPortalMatrix = FMatrix::Identity;
	}

	FVector2D trackingToPortalTranslation = FVector2D(trackingToPortalMatrix.M[0][2], trackingToPortalMatrix.M[1][2]);
	float trackingToPortalRotation;
	FVector2D trackingToPortalScale;

	if (GamespaceCalibration.version() < 2)
	{
		auto trs = Decomposes3x3TRS(trackingToPortalMatrix);
		trackingToPortalRotation = trs.Get<1>();
		trackingToPortalScale = trs.Get<2>();
	}
	else {
		trackingToPortalRotation = GamespaceCalibration.rotation();
		trackingToPortalScale = FVector2D(GamespaceCalibration.scale().x(), GamespaceCalibration.scale().y());
	}

	// for gen 1: all these operations should have been on the identity and result in the identity matrix again.
	auto trackingToArenaMatrix = FromTranslation(trackingToPortalTranslation / trackingToPortalScale) * FromRotation(trackingToPortalRotation);

	FVector2D trackingDimensions = FVector2D::ZeroVector;
	for (auto trackingPt : GetSiteInfo().MapBounds.BoundaryVertices) {
		trackingDimensions.X = FMath::Max(trackingPt.X, trackingDimensions.X);
		trackingDimensions.Y = FMath::Max(trackingPt.Y, trackingDimensions.Y);
	}

	FVector2D arenaToContentScale;
	if (ContentDimensions != FVector2D::ZeroVector && trackingDimensions != FVector2D::ZeroVector)
		arenaToContentScale = switchComponents(ContentDimensions) / switchComponents(trackingDimensions) * trackingToPortalScale;
	else
		arenaToContentScale = FVector2D(1.0f, 1.0f);
	auto arenaToContentMatrix = FromScale(arenaToContentScale);

	FZLSpaceCalibration calibration;
	calibration.ArenaToContentMatrix = switchMatrix(arenaToContentMatrix);
	calibration.TrackingToArenaMatrix = switchMatrix(trackingToArenaMatrix);
	calibration.TrackingToContentMatrix = switchMatrix(arenaToContentMatrix * trackingToArenaMatrix);

	calibration.ContentToArenaMatrix = calibration.ArenaToContentMatrix.Inverse();
	calibration.ArenaToTrackingMatrix = calibration.TrackingToArenaMatrix.Inverse();
	calibration.ContentToTrackingMatrix = calibration.TrackingToContentMatrix.Inverse();

	// tracking to portal rotation == tracking to arena rotation == tracking to content rotation, because there are no rotations from portal to arena and arena to content.
	FQuat trackingToPortalQuat = FQuat::MakeFromEuler(FVector(0.0f, 0.0f, FMath::RadiansToDegrees(trackingToPortalRotation)));
	calibration.TrackingToArenaQuat = trackingToPortalQuat;
	calibration.ArenaToContentQuat = FQuat::Identity;
	calibration.TrackingToContentQuat = trackingToPortalQuat;

	return calibration;
}

EZLGameState FZLCoreModule::GetGameState()
{
	return zl::ToStruct(zl::GetGameState());
}

FZLSession FZLCoreModule::GetSession()
{
	return zl::ToStruct(zl::GetSession());
}

FZLPlayerProfileMaps FZLCoreModule::GetPlayerProfileMaps()
{
	return zl::ToStruct(zl::GetPlayerProfileMaps());
}

FZLGameMasterView FZLCoreModule::GetGameMasterView()
{
	return zl::ToStruct(zl::GetGameMasterView());
}

FZLSite FZLCoreModule::GetSiteInfo()
{
	auto site = zl::ToStruct(zl::GetSiteInfo());
	if (ContentMapBounds.Contains(site.ContentMap))
		site.MapBounds = ContentMapBounds[site.ContentMap];
	return site;
}

FZLBackpackStatus FZLCoreModule::GetBackpackStatus()
{
	FZLBackpackStatus status = zl::ToStruct(zl::GetBackpackStatus());
	return status;
}

FZLLauncherInfo FZLCoreModule::GetLauncherInfo()
{
	FZLLauncherInfo info = zl::ToStruct(zl::GetLauncherInfo());
	return info;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FZLCoreModule, ZLCore)
