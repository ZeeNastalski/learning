#include "ZLConsoleCommands.h"

#include "ZLCoreBlueprintFunctionLibrary.h"
#include "ZLStructs.h"

#include "Modules/ModuleManager.h"
#include "Tickable.h"
#include "EngineMinimal.h"

#include <Engine/Console.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include <Engine/LocalPlayer.h>
#include <Kismet/GameplayStatics.h>

void LogToViewport(UWorld* world, FString string)
{
	APlayerController* PC = (world ? UGameplayStatics::GetPlayerController(world, 0) : NULL);
	ULocalPlayer* LocalPlayer = (PC ? Cast<ULocalPlayer>(PC->Player) : NULL);
	if (LocalPlayer && LocalPlayer->ViewportClient && LocalPlayer->ViewportClient->ViewportConsole)
	{
		LocalPlayer->ViewportClient->ViewportConsole->OutputText(string);
	}
}

void LogAll(UWorld* world, FString string)
{
	// To viewport console
	LogToViewport(world, string);

	// To output log
	UE_LOG(LogTemp, Log, TEXT("%s"), *string);

	// To screen
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, string);
}

template <typename EnumType>
EnumType GetEnumValueFromString(const FString& EnumName, const FString& String)
{
	UEnum* Enum = FindObject<UEnum>(ANY_PACKAGE, *EnumName, true);
	if (!Enum)
	{
		return EnumType(0);
	}
	return (EnumType)Enum->FindEnumIndex(FName(*String));
}

template <typename EnumType>
FString GetStringFromEnumValue(const FString& EnumName, EnumType EnumValue) {
	UEnum* Enum = FindObject<UEnum>(ANY_PACKAGE, *EnumName, true);
	if (!Enum)
	{
		return FString("Invalid - are you sure enum uses UENUM() macro?");
	}
	return Enum->GetNameByValue((int64) EnumValue).ToString();
}

bool ValidArguments(UWorld* world, const TArray<FString>& args, int numExpected)
{
	if (args.Num() != numExpected)
	{
		LogAll(world, FString::Printf(TEXT("Command expected %i arguments, but got %i"), numExpected, args.Num()));
		return false;
	}

	return true;
}

FAutoConsoleCommand* AssignClientProfileCommand;
FAutoConsoleCommand* UnassignClientProfileCommand;
FAutoConsoleCommand* SetGameStateCommand;
FAutoConsoleCommand* EndGameCommand;
FAutoConsoleCommand* SetPlayerScoreCommand;
FAutoConsoleCommand* SetPlayerStatCommand;
FAutoConsoleCommand* PrintPlayerScoreCommand;
FAutoConsoleCommand* PrintPlayerStatCommand;
FAutoConsoleCommand* PrintSiteInfoCommand;

void RegisterConsoleCommands()
{
	AssignClientProfileCommand = new FAutoConsoleCommand(
		TEXT("ZLAssignClientProfile"),
		TEXT("Assigns a profile id to a client (backpack) ip"),
		FConsoleCommandWithWorldArgsAndOutputDeviceDelegate::CreateLambda([](const TArray<FString>& args, UWorld* world, FOutputDevice& device)
		{
			if (!ValidArguments(world, args, 2)) return;

			FString clientIpAddress = args[0];
			int newProfileId = FCString::Atoi(*args[1]);
			
			UZLCoreBlueprintFunctionLibrary::AssignClientProfile(clientIpAddress, newProfileId);
		})
	);

	UnassignClientProfileCommand = new FAutoConsoleCommand(
		TEXT("ZLUnassignClientProfile"),
		TEXT("Unassigns a profile id that is associated with a client (backpack) ip"),
		FConsoleCommandWithWorldArgsAndOutputDeviceDelegate::CreateLambda([](const TArray<FString>& args, UWorld* world, FOutputDevice& device)
		{
			if (!ValidArguments(world, args, 1)) return;

			FString clientIpAddress = args[0];
			
			UZLCoreBlueprintFunctionLibrary::UnassignClientProfile(clientIpAddress);
		})
	);

	SetGameStateCommand = new FAutoConsoleCommand(
		TEXT("ZLSetGameState"),
		TEXT("Sets the Game State. Possible values are START, RUNNING, END, PAUSED"),
		FConsoleCommandWithWorldArgsAndOutputDeviceDelegate::CreateLambda([](const TArray<FString>& args, UWorld* world, FOutputDevice& device)
		{
			if (!ValidArguments(world, args, 1)) return;

			EZLGameState newState = GetEnumValueFromString<EZLGameState>("EZLGameState", args[0]);
			
			UZLCoreBlueprintFunctionLibrary::SetGameState(newState);
		})
	);

	EndGameCommand = new FAutoConsoleCommand(
		TEXT("ZLEndGame"),
		TEXT("Ends the Zero Latency game."),
		FConsoleCommandWithWorldArgsAndOutputDeviceDelegate::CreateLambda([](const TArray<FString>& args, UWorld* world, FOutputDevice& device)
		{
			UZLCoreBlueprintFunctionLibrary::EndGame();
		})
	);

	SetPlayerScoreCommand = new FAutoConsoleCommand(
		TEXT("ZLSetPlayerScore"),
		TEXT("Sets the player (client) score to an integer value"),
		FConsoleCommandWithWorldArgsAndOutputDeviceDelegate::CreateLambda([](const TArray<FString>& args, UWorld* world, FOutputDevice& device)
		{
			if (!ValidArguments(world, args, 2)) return;

			FString clientIpAddress = args[0];
			int score = FCString::Atoi(*args[1]);

			UZLCoreBlueprintFunctionLibrary::SetPlayerScore(clientIpAddress, score);
		})
	);

	SetPlayerStatCommand = new FAutoConsoleCommand(
		TEXT("ZLSetPlayerStat"),
		TEXT("Sets the player (client) stat of area id and stat id to a number value"),
		FConsoleCommandWithWorldArgsAndOutputDeviceDelegate::CreateLambda([](const TArray<FString>& args, UWorld* world, FOutputDevice& device)
		{
			if (!ValidArguments(world, args, 4)) return;

			FString clientIpAddress = args[0];
			FString areaId = args[1];
			FString statId = args[2];
			float value = FCString::Atoi(*args[3]);

			UZLCoreBlueprintFunctionLibrary::SetPlayerStat(clientIpAddress, areaId, statId, value);
		})
	);

	PrintPlayerScoreCommand = new FAutoConsoleCommand(
		TEXT("ZLPrintPlayerScore"),
		TEXT("Prints the player (client) score to the screen and console"),
		FConsoleCommandWithWorldArgsAndOutputDeviceDelegate::CreateLambda([](const TArray<FString>& args, UWorld* world, FOutputDevice& device)
		{
			if (!ValidArguments(world, args, 1)) return;

			FString clientIpAddress = args[0];
			
			int score = UZLCoreBlueprintFunctionLibrary::GetPlayerScore(clientIpAddress);

			LogAll(world, FString::Printf(TEXT("player score = %i"), score));
		})
	);

	PrintPlayerStatCommand = new FAutoConsoleCommand(
		TEXT("ZLPrintPlayerStat"),
		TEXT("Prints the player (client) stat to the screen and console"),
		FConsoleCommandWithWorldArgsAndOutputDeviceDelegate::CreateLambda([](const TArray<FString>& args, UWorld* world, FOutputDevice& device)
		{
			if (!ValidArguments(world, args, 3)) return;

			FString clientIpAddress = args[0];
			FString areaId = args[1];
			FString statId = args[2];

			float value = UZLCoreBlueprintFunctionLibrary::GetPlayerStat(clientIpAddress, areaId, statId);

			LogAll(world, FString::Printf(TEXT("'%s/%s' player stat = %f"), *areaId, *statId, value));
		})
	);

	PrintSiteInfoCommand = new FAutoConsoleCommand(
		TEXT("ZLPrintSiteInfo"),
		TEXT("Prints the site-related info to the screen and console"),
		FConsoleCommandWithWorldArgsAndOutputDeviceDelegate::CreateLambda([](const TArray<FString>& args, UWorld* world, FOutputDevice& device)
		{
			auto siteInfo = UZLCoreBlueprintFunctionLibrary::GetSiteInfo();

			FString obstaclesStr;
			if (siteInfo.MapBounds.Obstacles.Num() > 0) {
				for (int32 i = 0; i < siteInfo.MapBounds.Obstacles.Num() - 1; ++i) {
					obstaclesStr += FString::FromInt(siteInfo.MapBounds.Obstacles[i].Vertices.Num());
					obstaclesStr += ", ";
				}
				obstaclesStr += FString::FromInt(siteInfo.MapBounds.Obstacles.Last().Vertices.Num());
			}
			else {
				obstaclesStr += "none";
			}

			LogAll(world, FString::Printf(TEXT("site: contentmap = %s, site id = %i, mapbounds = #%i, (%s)"), *GetStringFromEnumValue("EContentMap", siteInfo.ContentMap), siteInfo.SiteId, siteInfo.MapBounds.BoundaryVertices.Num(), *obstaclesStr));
		})
	);
}

void DeregisterConsoleCommands()
{
	delete AssignClientProfileCommand;
	delete UnassignClientProfileCommand;
	delete SetGameStateCommand;
	delete EndGameCommand;
	delete SetPlayerScoreCommand;
	delete SetPlayerStatCommand;
	delete PrintPlayerScoreCommand;
	delete PrintPlayerStatCommand;
	delete PrintSiteInfoCommand;
}