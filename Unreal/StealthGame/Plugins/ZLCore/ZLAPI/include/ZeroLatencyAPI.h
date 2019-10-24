#pragma once

namespace zl
{
	namespace proto
	{
		namespace controller
		{
			class Input;
		}

		namespace player
		{
			class Profile;
			class StatsMap;
			class PlayerTrackingData;
		}

		namespace launcher
		{
			class LauncherInfo;
		}

		class GameHeartbeat;
		class GameSpaceCalibration;
		class GameState;
		enum EGameState;
		class Session;
		class MapBounds;
		class GameMasterView;
		class ProfileMaps;
		class Transmission;
		class GameMasterView;
		class GameResults;
		class BackpackStatus;
		class Site;
	}

	enum ELoggingLevel;

	//Call when your app should begin interacting with the zero latency api
	extern void Start(ELoggingLevel loggingLevel);
	//Call when your app should stop interacting with the api
	extern void Stop();
	//Called once per tick of the game thread of your app
	extern void Tick(const int FPS);
	
	extern const proto::controller::Input& GetControllerInput();
	extern const proto::GameSpaceCalibration& GetGameSpaceCalibration();
	extern const proto::GameState& GetGameState();
	extern const proto::Session& GetSession();
	extern const proto::Site& GetSiteInfo();
	extern const proto::GameMasterView& GetGameMasterView();
	extern const proto::ProfileMaps& GetPlayerProfileMaps();	
	extern const proto::BackpackStatus& GetBackpackStatus();
	extern const proto::launcher::LauncherInfo& GetLauncherInfo();

	//TODO: this can be easily templated
	typedef void(*ControllerInputChangedCallback)(const proto::controller::Input&);
	typedef void(*GameSpaceCalibrationChangedCallback)(const proto::GameSpaceCalibration&);
	typedef void(*GameStateChangedCallback)(const proto::GameState&);
	typedef void(*SessionChangedCallback)(const proto::Session&);
	typedef void(*SiteInfoChangedCallback)(const proto::Site&);
	typedef void(*GameMasterViewChangedCallback)(const proto::GameMasterView&);
	typedef void(*PlayerProfileMapsChangedCallback)(const proto::ProfileMaps&);
	typedef void(*LauncherInfoChangedCallback)(const proto::launcher::LauncherInfo&);

	extern void SetControllerInputChangedCallback(ControllerInputChangedCallback callback);
	extern void SetGameSpaceCalibrationChangedCallback(GameSpaceCalibrationChangedCallback callback);
	extern void SetGameStateChangedCallback(GameStateChangedCallback callback);
	extern void SetSessionChangedCallback(SessionChangedCallback callback);
	extern void SetSiteInfoChangedCallback(SiteInfoChangedCallback callback);
	extern void SetGameMasterViewChangedCallback(GameMasterViewChangedCallback callback);
	extern void SetPlayerProfileMapsChangedCallback(PlayerProfileMapsChangedCallback callback);
	extern void SetLauncherInfoChangedCallback(LauncherInfoChangedCallback callback);

	extern void AssignClientProfile(const char* clientIp, int newProfileId);
	extern void UnassignClientProfile(const char* clientIp);
	
	extern int GetDebugStateDumpString(char* buffer, int bufferLength);

	extern void SetGameState(proto::EGameState newState);

	extern void SetPlayerStats(proto::player::StatsMap newStats);
	extern void EndGame(proto::GameResults gameResults);

	/// Set by ZLSteamVR every frame with player posiiton data
	extern void SetPlayerTrackingData(proto::player::PlayerTrackingData trackingData);
}