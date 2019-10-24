#pragma once

#include "CoreMinimal.h"
#include "ZLStructs.h"

#include "ZLCallbackHandler.generated.h"

/*
Broadcasts whenever new information about a blaster's input state is received.
*/
DECLARE_MULTICAST_DELEGATE_OneParam(FBlasterInputUpdateSignature, const FZLBlasterInput&);

/*
This will probably dissapear in the near future as devs don't need to see this.
*/
DECLARE_MULTICAST_DELEGATE_SixParams(FGamespaceCalibrationUpdateSignature, float, float, float, float, float, float);

/*
Broadcasts whenever new information about whether the game is paused or not is received.
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameStateUpdatedSignature, EZLGameState, State);

/*
Broadcasts when we get updated information about the date and time of the current session. Only used in an edge case right now. Will probably dissapear in the future.
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSessionUpdatedSignature, const FZLSession&, Session);

/*
Broadcasts whenever new information regarding the site is received.
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSiteInfoUpdatedSignature, const FZLSite&, SiteInfo);

/*
Broadcasts whenever new information regarding the layout of the game master is received.
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameMasterViewUpdatedSignature, const FZLGameMasterView&, GameMasterView);

/*
Broadcasts whenever new information regarding the 
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerProfileMapsUpdatedSignature, const FZLPlayerProfileMaps&, PlayerProfileMaps);

/*
Broadcasts whenever new information regarding the launcher info (such as app mode) is received.
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLauncherInfoUpdatedSignature, const FZLLauncherInfo&, LauncherInfo);

/*
This class performas the job of patching the ZLBlueprintFunctionLibrary class through to delegates.
*/
UCLASS()
class UZLCallbackHandler : public UObject
{
	GENERATED_BODY()

public:
	/*
	Client only.
	Not Blueprintable.
	*/
	FBlasterInputUpdateSignature OnBlasterInputUpdated;

	/*
	Client only.
	Not Blueprintable.
	*/
	FGamespaceCalibrationUpdateSignature OnGamespaceCalibrationUpdated;

	/*
	Server only.
	Blueprintable.
	*/
	UPROPERTY(BlueprintAssignable, Category=Default)
	FGameStateUpdatedSignature OnGameStateUpdated;

	/*
	Server only.
	Blueprintable.
	*/
	UPROPERTY(BlueprintAssignable, Category = Default)
	FSessionUpdatedSignature OnSessionUpdated;

	/*
	Server and client.
	Blueprintable.
	*/
	UPROPERTY(BlueprintAssignable, Category=Default)
	FSiteInfoUpdatedSignature OnSiteInfoUpdated;

	/*
	Server and game master.
	Blueprintable.
	*/
	UPROPERTY(BlueprintAssignable, Category = Default)
	FGameMasterViewUpdatedSignature OnGameMasterViewUpdated;

	/*
	Server only.
	Blueprintable.
	*/
	UPROPERTY(BlueprintAssignable, Category = Default)
	FPlayerProfileMapsUpdatedSignature OnPlayerProfileMapsUpdated;

	/*
	All modes.
	Blueprintable.
	*/
	UPROPERTY(BlueprintAssignable, Category = Default)
	FLauncherInfoUpdatedSignature OnLauncherInfoUpdated;
};