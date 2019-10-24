// Fill out your copyright notice in the Description page of Project Settings.

#include "ZLGameViewportClient.h"
#include "Engine.h"

//#include "ZLLauncherState.h"
//#include "ZLPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LocalPlayer.h"
//#include "ZLGameMode.h"
#include "ZLCoreBlueprintFunctionLibrary.h"

UZLGameViewportClient::UZLGameViewportClient(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
	//Add 9 additional settings for 0-8 players
	for (int x = 0; x < 9; ++x)
	{
		SplitscreenInfo.Add(FSplitscreenData());
	}
	//No players - still full screen
	SplitscreenInfo[EZLSplitScreenType::NoPlayers].PlayerData.Add(FPerPlayerSplitscreenData(1.0f, 1.0f, 0.0f, 0.0f)); //Size X, Size Y, Origin X, Origin Y
	//One plyaer
	SplitscreenInfo[EZLSplitScreenType::OnePlayer].PlayerData.Add(FPerPlayerSplitscreenData(1.0f, 1.0f, 0.0f, 0.0f));
	//Two players
	SplitscreenInfo[EZLSplitScreenType::TwoPlayers].PlayerData.Add(FPerPlayerSplitscreenData(1.0f, 0.5f, 0.0f, 0.0f)); //Top Row
	SplitscreenInfo[EZLSplitScreenType::TwoPlayers].PlayerData.Add(FPerPlayerSplitscreenData(1.0f, 0.5f, 0.0f, 0.5f)); //Bottom Row
	//Three players
	SplitscreenInfo[EZLSplitScreenType::ThreePlayers].PlayerData.Add(FPerPlayerSplitscreenData(0.5f, 0.5f, 0.0f, 0.0f)); //Top Row
	SplitscreenInfo[EZLSplitScreenType::ThreePlayers].PlayerData.Add(FPerPlayerSplitscreenData(0.5f, 0.5f, 0.5f, 0.0f)); //Top Row
	SplitscreenInfo[EZLSplitScreenType::ThreePlayers].PlayerData.Add(FPerPlayerSplitscreenData(1.0f, 0.5f, 0.0f, 0.5f)); //Bottom Row
	//Four players
	SplitscreenInfo[EZLSplitScreenType::FourPlayers].PlayerData.Add(FPerPlayerSplitscreenData(0.5f, 0.5f, 0.0f, 0.0f)); //Top Row
	SplitscreenInfo[EZLSplitScreenType::FourPlayers].PlayerData.Add(FPerPlayerSplitscreenData(0.5f, 0.5f, 0.5f, 0.0f)); //Top Row
	SplitscreenInfo[EZLSplitScreenType::FourPlayers].PlayerData.Add(FPerPlayerSplitscreenData(0.5f, 0.5f, 0.0f, 0.5f)); //Bottom Row
	SplitscreenInfo[EZLSplitScreenType::FourPlayers].PlayerData.Add(FPerPlayerSplitscreenData(0.5f, 0.5f, 0.5f, 0.5f)); //Bottom Row
	//Five players
	SplitscreenInfo[EZLSplitScreenType::FivePlayers].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 0.0f, 0.0f)); //Top Row
	SplitscreenInfo[EZLSplitScreenType::FivePlayers].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 1.f / 3.f, 0.0f)); //Top Row
	SplitscreenInfo[EZLSplitScreenType::FivePlayers].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 2.f / 3.f, 0.0f)); //Top Row
	SplitscreenInfo[EZLSplitScreenType::FivePlayers].PlayerData.Add(FPerPlayerSplitscreenData(0.5, 0.5f, 0.0f, 0.5f)); //Bottom Row
	SplitscreenInfo[EZLSplitScreenType::FivePlayers].PlayerData.Add(FPerPlayerSplitscreenData(0.5, 0.5f, 0.5f, 0.5f)); //Bottom Row
	//Six players
	SplitscreenInfo[EZLSplitScreenType::SixPlayers].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 0.0f, 0.0f)); //Top Row
	SplitscreenInfo[EZLSplitScreenType::SixPlayers].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 1.f / 3.f, 0.0f)); //Top Row
	SplitscreenInfo[EZLSplitScreenType::SixPlayers].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 2.f / 3.f, 0.0f)); //Top Row
	SplitscreenInfo[EZLSplitScreenType::SixPlayers].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 0.0f, 0.5f)); //Bottom Row
	SplitscreenInfo[EZLSplitScreenType::SixPlayers].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 1.f / 3.f, 0.5f)); //Bottom Row
	SplitscreenInfo[EZLSplitScreenType::SixPlayers].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 2.f / 3.f, 0.5f)); //Bottom Row
	//Seven players
	SplitscreenInfo[EZLSplitScreenType::SevenPlayers].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.0f, 0.0f)); //Top Row
	SplitscreenInfo[EZLSplitScreenType::SevenPlayers].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.25f, 0.0f)); //Top Row
	SplitscreenInfo[EZLSplitScreenType::SevenPlayers].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.5f, 0.0f)); //Top Row
	SplitscreenInfo[EZLSplitScreenType::SevenPlayers].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.75f, 0.0f)); //Top Row
	SplitscreenInfo[EZLSplitScreenType::SevenPlayers].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 0.0f, 0.5f)); //Bottom Row
	SplitscreenInfo[EZLSplitScreenType::SevenPlayers].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 1.f / 3.f, 0.5f)); //Bottom Row
	SplitscreenInfo[EZLSplitScreenType::SevenPlayers].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 2.f / 3.f, 0.5f)); //Bottom Row
	//Eight players
	SplitscreenInfo[EZLSplitScreenType::EightPlayers].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.0f, 0.0f)); //Top Row
	SplitscreenInfo[EZLSplitScreenType::EightPlayers].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.25f, 0.0f)); //Top Row
	SplitscreenInfo[EZLSplitScreenType::EightPlayers].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.5f, 0.0f)); //Top Row
	SplitscreenInfo[EZLSplitScreenType::EightPlayers].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.75f, 0.0f)); //Top Row
	SplitscreenInfo[EZLSplitScreenType::EightPlayers].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.0f, 0.5f)); //Bottom Row
	SplitscreenInfo[EZLSplitScreenType::EightPlayers].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.25f, 0.5f)); //Bottom Row
	SplitscreenInfo[EZLSplitScreenType::EightPlayers].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.5f, 0.5f)); //Bottom Row
	SplitscreenInfo[EZLSplitScreenType::EightPlayers].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.75f, 0.5f)); //Bottom Row

	//Ensure we can create enough players
	MaxSplitscreenPlayers = 9;	
}

void UZLGameViewportClient::UpdateActiveSplitscreenType()
{
	//Super::UpdateActiveSplitscreenType();
}



void UZLGameViewportClient::Tick(float DeltaTime)
{
	AGameStateBase* GS = GetWorld()->GetGameState();
	ELauncherMode mode = UZLCoreBlueprintFunctionLibrary::GetLauncherMode();

	if (mode == ELauncherMode::UNKNOWN || mode == ELauncherMode::BACKPACK)
	{
		// Don't do anything for backpack
		Super::Tick(DeltaTime);
		return;
	}


	if (mode != ELauncherMode::GAME_MASTER)
	{
		Super::Tick(DeltaTime);
		return;
	}

	if (GS)
	{
		int32 PlayerCount = GS->PlayerArray.Num();
		
		TArray<uint32> PlayerIdsToAdd;
		TArray<uint32> PlayerIdsToRemove;

		//make sure all remote players have corresponding local player for viewport mirroring
		for (APlayerState* player : GS->PlayerArray)
		{
			// skip local local player states
			//if(player->SavedNetworkAddress.IsEmpty()) continue;
			
			// skip remote players without pawn
			APawn* pawn = PawnForPlayerId(player->PlayerId);
			if(!pawn) continue; 

			// skip players that other than the ZL player pawn
			if(!pawn->GetName().Contains(TEXT("BP_Player"))) continue;

			// found a remote player that's not gm or spectator and has a pawn, Add it.
			if (!LocalPlayerMap.Contains(player->PlayerId))
			{
				PlayerIdsToAdd.Add(player->PlayerId);
			}			
		}

		for (auto& mapping : LocalPlayerMap)
		{
			int32 id = mapping.Key;
			APlayerController* LocalPC = mapping.Value;

			// if GS->PlayerArray does not contain a player state of the PlayerId equal id
			if (!GS->PlayerArray.ContainsByPredicate([&](APlayerState* state) { return state->PlayerId == id; }))
			{
				PlayerIdsToRemove.Add(id);
			}
		}

		// Add local players mirroring remote players
		for (int32 id : PlayerIdsToAdd)
		{
			APawn* remotePawn = PawnForPlayerId(id);

			//if (mode != ELauncherMode::GAME_MASTER)
			{
				APlayerController* localPlayer = CreatePlayer(this, -1, true);


				if (localPlayer)
				{
					LocalPlayerMap.Add(id, localPlayer);
					localPlayer->SetName(ModeString() + TEXT("_") + remotePawn->GetName() + TEXT("_Local_") + FPlatformProcess::ComputerName());
					localPlayer->SetReplicates(false);
				}
				else
				{
					UE_LOG(LogTemp, Log, TEXT("Failed to create local player for remote player %d"), id);
				}
			}
		}

		// Remove local mirroring players if their remote counterparts are no longer present
		for (int32 id : PlayerIdsToRemove)
		{
			APlayerController* LocalPC = LocalPlayerMap[id];
			LocalPlayerMap.Remove(id);
			UGameplayStatics::RemovePlayer(LocalPC, true);
		}


		//Keep view target in sync
		for (auto& mapping : LocalPlayerMap)
		{
			int32 id = mapping.Key;
			APlayerController* player = mapping.Value;
			APawn* pawn = PawnForPlayerId(id);
			player->SetViewTarget(pawn);
		}

	}

	LayoutPlayers();
	Super::Tick(DeltaTime);
}



APawn* UZLGameViewportClient::PawnForPlayerId(int32 id)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawn::StaticClass(), FoundActors);

	for (AActor* act : FoundActors)
	{
		APawn* pawn = Cast<APawn>(act);
		
		if(!pawn) continue;
		if(!pawn->PlayerState) continue;
		if (pawn->PlayerState->PlayerId == id) return pawn;
	}

	return nullptr;
}

FString UZLGameViewportClient::ModeString()
{
	ELauncherMode mode = UZLCoreBlueprintFunctionLibrary::GetLauncherMode();	

	if (mode == ELauncherMode::SERVER)
	{
		return FString(TEXT("SERVER"));
	}

	if (mode == ELauncherMode::BACKPACK)
	{
		return FString(TEXT("BACKPACK"));
	}

	if (mode == ELauncherMode::GAME_MASTER)
	{
		return FString(TEXT("GAME_MASTER"));
	}

	if (mode == ELauncherMode::SPECTATOR)
	{
		return FString(TEXT("SPECTATOR"));
	}

	return "UNKNOWN";
}


void UZLGameViewportClient::LayoutPlayers()
{

	ELauncherMode mode = UZLCoreBlueprintFunctionLibrary::GetLauncherMode();
	int32 RemotePlayerCount = LocalPlayerMap.Num();
	AGameStateBase* GS = GetWorld()->GetGameState();


	if (!GS)
	{
		// return if no GameState
		Super::LayoutPlayers();
		return;
	}

	/*
	if (mode == ELauncherMode::UNKNOWN || mode == ELauncherMode::BACKPACK)
	{
		Super::LayoutPlayers();
		return;
	}
	*/

	if (mode != ELauncherMode::GAME_MASTER)
	{
		Super::LayoutPlayers();
		return;
	}

	// There are no remote players. In this case we show the view of the default local player
	if (RemotePlayerCount == 0)
	{
		APlayerController* DefaultPC = UGameplayStatics::GetPlayerController(this, 0);
		if (DefaultPC)
		{
			ULocalPlayer* LP = DefaultPC->GetLocalPlayer();

			LP->Size.X = SplitscreenInfo[EZLSplitScreenType::NoPlayers].PlayerData[0].SizeX;		// 1
			LP->Size.Y = SplitscreenInfo[EZLSplitScreenType::NoPlayers].PlayerData[0].SizeY;		// 1
			LP->Origin.X = SplitscreenInfo[EZLSplitScreenType::NoPlayers].PlayerData[0].OriginX;	// 0
			LP->Origin.Y = SplitscreenInfo[EZLSplitScreenType::NoPlayers].PlayerData[0].OriginY;	// 0
		}
		return;
	}


	/*
	FZLGameMasterView gmview = UZLCoreBlueprintFunctionLibrary::GetGameMasterView();

	int32 PlayerCount = 0;
	for (auto row : gmview.Rows)
	{
		PlayerCount += row.ViewIps.Num();
	}
	*/
		

	//Set up the enum index for our split screen
	int32 EnumIndex = static_cast<int32>(ESplitScreenType::SplitTypeCount);
	EnumIndex += RemotePlayerCount;


	//First, hide all viewports for all local players
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PC = Iterator->Get();
		ULocalPlayer* LPlayer = PC->GetLocalPlayer();
		if (LPlayer)
		{
			LPlayer->Size.X = 0;
			LPlayer->Size.Y = 0;
			LPlayer->Origin.X = 0;
			LPlayer->Origin.Y = 0;
		}			
	}


	//Second, unhide local player viewports and position them on the screen.
	int32 CurrentPlayerViewportLocation = 0;
	for(auto& element : LocalPlayerMap)		
	{
		int32 remotePlayerId = element.Key;
		APlayerController* PC = element.Value;
	
		//We need the player controller
		if (PC)
		{			
			ULocalPlayer* LPlayer = PC->GetLocalPlayer();
							
			if (LPlayer)
			{					
				//Set the viewport size for this player
				LPlayer->Size.X = SplitscreenInfo[EnumIndex].PlayerData[CurrentPlayerViewportLocation].SizeX;
				LPlayer->Size.Y = SplitscreenInfo[EnumIndex].PlayerData[CurrentPlayerViewportLocation].SizeY;
				LPlayer->Origin.X = SplitscreenInfo[EnumIndex].PlayerData[CurrentPlayerViewportLocation].OriginX;
				LPlayer->Origin.Y = SplitscreenInfo[EnumIndex].PlayerData[CurrentPlayerViewportLocation].OriginY;

				//Increment for the next player
				++CurrentPlayerViewportLocation;									
			}
		}
	}		
}

APlayerController* UZLGameViewportClient::CreatePlayer(const UObject* WorldContextObject, int32 ControllerId, bool bSpawnPawn)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	FString Error;

	ULocalPlayer* LocalPlayer = World ? World->GetGameInstance()->CreateLocalPlayer(ControllerId, Error, bSpawnPawn) : NULL;

	if (Error.Len() > 0)
	{
		UE_LOG(LogPlayerManagement, Error, TEXT("Failed to Create Player: %s"), *Error);
	}

	return (LocalPlayer ? LocalPlayer->PlayerController : nullptr);
}

ULocalPlayer* UZLGameViewportClient::CreateLocalPlayer(const UObject* WorldContextObject, int32 ControllerId, bool bSpawnPawn)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	FString Error;

	ULocalPlayer* LocalPlayer = World ? World->GetGameInstance()->CreateLocalPlayer(ControllerId, Error, bSpawnPawn) : NULL;

	if (Error.Len() > 0)
	{
		UE_LOG(LogPlayerManagement, Error, TEXT("Failed to Create Player: %s"), *Error);
	}

	return LocalPlayer;
}




