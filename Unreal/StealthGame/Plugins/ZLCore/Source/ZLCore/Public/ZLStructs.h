#pragma once

#include "CoreMinimal.h"

#include "ZLStructs.generated.h"

/*
Describes the state of the pump action on a blaster.
*/
UENUM(BlueprintType)
enum class EBlasterPumpState : uint8
{
	PUMP_IDLE,
	PUMP_FORWARD,
	PUMP_BACK
};

/*
Describes the mode the launcher is in.
*/
UENUM(BlueprintType)
enum class ELauncherMode : uint8
{
	UNKNOWN = 0,
	SERVER = 1,
	BACKPACK = 2,
	GAME_MASTER = 3,
	SPECTATOR = 4
};

/*
Describes whether the game is paused or not.
*/
UENUM()
enum class EZLGameState : uint8
{
	Start,
	Running,
	End,
	Paused
};

/*
Which type of content the site supports.
*/
UENUM()
enum class EContentMap : uint8
{
	Unknown = 0,
	SteelStreet = 3, // Gen 1: The original
	Square15x15WithPillar = 4, // Gen 2: official support
	Orlando = 9, // Gen 1: 18.75 x 10 with 2 pillars
	KalahariPoconos = 11, // Gen 1: 15x15 with pillar + intrusion
	KalahariDells = 13, // Gen 1: 15x15 with 2 pillars
	Rectangle20x9p6 = 18, // Gen 2: official support
	Square15x15NoPillar = 50, // Gen 2: official support
	Tongyeong = 51, // Gen 2 (custom): 10x10 with a center pillar
};

/*
Describes the input state of a blaster. That is which triggers/buttons are pressed and what state is the pump in.
*/
struct ZLCORE_API FZLBlasterInput
{
	bool TriggerPulled;

	bool SideButtonPressed;

	bool BottomButtonPressed;

	EBlasterPumpState PumpState;
};



/*
Descibes a player's gender.
*/
UENUM()
enum class EZLGender : uint8
{
	Female,
	Male,
	Other
};

USTRUCT(BlueprintType)
struct FZLLauncherInfo
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	ELauncherMode Mode;
};

/*
Profile information as described in a player's customer login information and from our operation's teams on site via the game master interface.
*/
USTRUCT(BlueprintType)
struct FZLProfile
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	FString FirstName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	FString LastName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	FString DisplayName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	FString FallbackName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	float Height;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	bool bLeftHanded;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	EZLGender Gender;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	FString Language;
};

/*
Session information. The profiles of all the players that have been booked into this session.
*/
USTRUCT(BlueprintType)
struct FZLSession
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	TMap<int32, FZLProfile> ProfilesByProfileId;
};

/*
An obstacle's boundary
*/
USTRUCT(BlueprintType)
struct FZLObstacleBounds
{
	GENERATED_BODY()

	FZLObstacleBounds() {}

	FZLObstacleBounds(const TArray<FVector2D>& v)
		: Vertices(v) {
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	TArray<FVector2D> Vertices;
};

/*
The site boundaries and obstacles in arena space.
*/
USTRUCT(BlueprintType)
struct FZLMapBounds
{
	GENERATED_BODY()

	FZLMapBounds() {}

	FZLMapBounds(const TArray<FVector2D>& bv, const TArray<FZLObstacleBounds>& o)
		: BoundaryVertices(bv), Obstacles(o) {
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	TArray<FVector2D> BoundaryVertices;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	TArray<FZLObstacleBounds> Obstacles;
};

/*
Info related to the site that in production shouldn't change during a game.
*/
USTRUCT(BlueprintType)
struct FZLSite
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	int SiteId;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	EContentMap ContentMap;

	// guarantees that one of the corners is (0, 0) and that it is the minimum value.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	FZLMapBounds MapBounds;
};

/*
Contains an array which represents the player views that should be displayed on the game master in a single row from left to right.
*/
USTRUCT(BlueprintType)
struct FZLGameMasterRow
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	TArray<FString> ViewIps;
};

/*
A list of rows from top to bottom of player views that the game master sees.
*/
USTRUCT(BlueprintType)
struct FZLGameMasterView
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	TArray<FZLGameMasterRow> Rows;
};

/*
A list of rows from top to bottom of player views that the game master sees.
*/
USTRUCT(BlueprintType)
struct FZLPlayerProfileMaps
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	TMap<FString, int32> IdsByClientIp;
};

USTRUCT(BlueprintType)
struct FZLPlayerAreaStats
{
	GENERATED_BODY()

	// Key is stat id/code (e.g. "ZombieKills", "Headshots")
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	TMap<FString, float> Stats;

	void SetStat(FString statId, double value)
	{
		if (Stats.Contains(statId))
		{
			Stats[statId] = value;
		}
		else
		{
			Stats.Add(statId, value);
		}
	}
};

USTRUCT(BlueprintType)
struct FZLPlayerStats
{
	GENERATED_BODY()

	// The total sum score
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	int Score = 0;

	// Key is area id/code (e.g. "Bunker", "Quarantine", "Rooftop")
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	TMap<FString, FZLPlayerAreaStats> AreaStats;

	void SetAreaStat(FString areaId, FString statId, double value)
	{
		if (AreaStats.Contains(areaId))
		{
			AreaStats[areaId].SetStat(statId, value);
		}
		else
		{
			FZLPlayerAreaStats NewAreaStats;
			NewAreaStats.SetStat(statId, value);
			AreaStats.Add(areaId, NewAreaStats);
		}
	}
};

USTRUCT(BlueprintType)
struct FZLPlayerStatsMap
{
	GENERATED_BODY()

	// Key is player/client address
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	TMap<FString, FZLPlayerStats> PlayerStats;

	void SetStat(FString clientIpAddress, FString areaId, FString statId, double value)
	{
		if (PlayerStats.Contains(clientIpAddress))
		{
			PlayerStats[clientIpAddress].SetAreaStat(areaId, statId, value);
		}
		else
		{
			FZLPlayerStats NewStats;
			NewStats.SetAreaStat(areaId, statId, value);
			PlayerStats.Add(clientIpAddress, NewStats);
		}
	}
};


/*
Player tracking informaton
*/
USTRUCT(BlueprintType)
struct FZLPlayerTrackingData
{
	GENERATED_BODY()
	
	// Head position in Arena space
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	FVector ArenaHeadPosition;

	// Head orientation in Arena space
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	FQuat ArenaHeadOrientation;

	// Head position in Tracking space (SteamVR space)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	FVector TrackingHeadPosition;

	// Head orientation in Tracking space (SteamVR space)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	FQuat TrackingHeadOrientation;

	// List of controller ids that are currently tracked by SteamVR
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	TArray<int32> TrackedControllers;
};

USTRUCT(BlueprintType)
struct FZLBackpackStatus
{
	GENERATED_BODY()
	
	// true if the the player has positional tracking
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	bool TrackingOk;

	// true if the ZL blaster is paired with the WMR controller
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	bool IsControllerHybrid;



	// WMR to Gun offsets
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	FVector RightControllerTranslationOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	FVector LeftControllerTranslationOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	FQuat LeftControllerRotationOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	FQuat RightControllerRotationOffset;
};

USTRUCT(BlueprintType)
struct FZLSpaceCalibration
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	FMatrix TrackingToArenaMatrix;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	FMatrix ArenaToContentMatrix;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	FMatrix TrackingToContentMatrix;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	FMatrix ArenaToTrackingMatrix;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	FMatrix ContentToArenaMatrix;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	FMatrix ContentToTrackingMatrix;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	FQuat TrackingToArenaQuat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	FQuat ArenaToContentQuat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	FQuat TrackingToContentQuat;
};