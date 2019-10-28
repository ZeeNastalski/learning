// Fill out your copyright notice in the Description page of Project Settings.

#include "ZLSplitScreenWidget.h"
#include "Components/CanvasPanel.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/Image.h"
#include "Brushes/SlateImageBrush.h"
#include "Components/CanvasPanelSlot.h"



void UZLSplitScreenWidget::NativeConstruct()
{
	//Add 9 additional settings for 0-8 players
	for (int x = 0; x < 9; ++x)
	{
		SplitScreenLookup.Add(FSplitscreenData());
	}
	//No players - still full screen
	SplitScreenLookup[0].PlayerData.Add(FPerPlayerSplitscreenData(1.0f, 1.0f, 0.0f, 0.0f)); //Size X, Size Y, Origin X, Origin Y
	
	//One player
	SplitScreenLookup[1].PlayerData.Add(FPerPlayerSplitscreenData(1.0f, 1.0f, 0.0f, 0.0f));
	
	//Two players
	SplitScreenLookup[2].PlayerData.Add(FPerPlayerSplitscreenData(1.0f, 0.5f, 0.0f, 0.0f)); //Top Row
	SplitScreenLookup[2].PlayerData.Add(FPerPlayerSplitscreenData(1.0f, 0.5f, 0.0f, 0.5f)); //Bottom Row
	
	//Three players
	SplitScreenLookup[3].PlayerData.Add(FPerPlayerSplitscreenData(0.5f, 0.5f, 0.0f, 0.0f)); //Top Row
	SplitScreenLookup[3].PlayerData.Add(FPerPlayerSplitscreenData(0.5f, 0.5f, 0.5f, 0.0f)); //Top Row
	SplitScreenLookup[3].PlayerData.Add(FPerPlayerSplitscreenData(1.0f, 0.5f, 0.0f, 0.5f)); //Bottom Row
	
	//Four players
	SplitScreenLookup[4].PlayerData.Add(FPerPlayerSplitscreenData(0.5f, 0.5f, 0.0f, 0.0f)); //Top Row
	SplitScreenLookup[4].PlayerData.Add(FPerPlayerSplitscreenData(0.5f, 0.5f, 0.5f, 0.0f)); //Top Row
	SplitScreenLookup[4].PlayerData.Add(FPerPlayerSplitscreenData(0.5f, 0.5f, 0.0f, 0.5f)); //Bottom Row
	SplitScreenLookup[4].PlayerData.Add(FPerPlayerSplitscreenData(0.5f, 0.5f, 0.5f, 0.5f)); //Bottom Row

	//Five players
	SplitScreenLookup[5].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 0.0f, 0.0f)); //Top Row
	SplitScreenLookup[5].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 1.f / 3.f, 0.0f)); //Top Row
	SplitScreenLookup[5].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 2.f / 3.f, 0.0f)); //Top Row
	SplitScreenLookup[5].PlayerData.Add(FPerPlayerSplitscreenData(0.5, 0.5f, 0.0f, 0.5f)); //Bottom Row
	SplitScreenLookup[5].PlayerData.Add(FPerPlayerSplitscreenData(0.5, 0.5f, 0.5f, 0.5f)); //Bottom Row

	//Six players
	SplitScreenLookup[6].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 0.0f, 0.0f)); //Top Row
	SplitScreenLookup[6].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 1.f / 3.f, 0.0f)); //Top Row
	SplitScreenLookup[6].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 2.f / 3.f, 0.0f)); //Top Row
	SplitScreenLookup[6].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 0.0f, 0.5f)); //Bottom Row
	SplitScreenLookup[6].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 1.f / 3.f, 0.5f)); //Bottom Row
	SplitScreenLookup[6].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 2.f / 3.f, 0.5f)); //Bottom Row

	//Seven players
	SplitScreenLookup[7].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.0f, 0.0f)); //Top Row
	SplitScreenLookup[7].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.25f, 0.0f)); //Top Row
	SplitScreenLookup[7].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.5f, 0.0f)); //Top Row
	SplitScreenLookup[7].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.75f, 0.0f)); //Top Row
	SplitScreenLookup[7].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 0.0f, 0.5f)); //Bottom Row
	SplitScreenLookup[7].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 1.f / 3.f, 0.5f)); //Bottom Row
	SplitScreenLookup[7].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 2.f / 3.f, 0.5f)); //Bottom Row

	//Eight players
	SplitScreenLookup[8].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.0f, 0.0f)); //Top Row
	SplitScreenLookup[8].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.25f, 0.0f)); //Top Row
	SplitScreenLookup[8].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.5f, 0.0f)); //Top Row
	SplitScreenLookup[8].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.75f, 0.0f)); //Top Row
	SplitScreenLookup[8].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.0f, 0.5f)); //Bottom Row
	SplitScreenLookup[8].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.25f, 0.5f)); //Bottom Row
	SplitScreenLookup[8].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.5f, 0.5f)); //Bottom Row
	SplitScreenLookup[8].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.75f, 0.5f)); //Bottom Row

	// Call the Blueprint "Event Construct" node
	Super::NativeConstruct();
}


void UZLSplitScreenWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{	
	Super::NativeTick(MyGeometry, InDeltaTime);
}

TArray<FSplitScreenView> UZLSplitScreenWidget::RebuildSplitScreen()
{
	UE_LOG(LogTemp, Log, TEXT("Rebuilding Split Screen"));

	TArray<FSplitScreenView> views;

	// The blueprint didn't assign the canvas yet
	if (!Canvas) return views;
	
	FVector2D CanvasSize = Canvas->GetCachedGeometry().GetLocalSize();
		
	// no point rendering if canvas size is 0 by 0
	if (CanvasSize == FVector2D::ZeroVector) return views;

	// find all scene capture 2d in pawns
	TArray<APawn*> players;
	FindSplitScreenPawns(players);
	UE_LOG(LogTemp, Log, TEXT("Split screen canvas dimension %f x %f, players: %d"), CanvasSize.X, CanvasSize.Y, players.Num());

	int PlayerCount = players.Num();

	for(int i = 0; i<PlayerCount; i++)
	{
		APawn* player = players[i];
				
		FSplitScreenView ssView;
		ssView.Origin.X = CanvasSize.X * SplitScreenLookup[PlayerCount].PlayerData[i].OriginX;
		ssView.Origin.Y = CanvasSize.Y * SplitScreenLookup[PlayerCount].PlayerData[i].OriginY;
		ssView.Size.X = CanvasSize.X * SplitScreenLookup[PlayerCount].PlayerData[i].SizeX;
		ssView.Size.Y = CanvasSize.Y * SplitScreenLookup[PlayerCount].PlayerData[i].SizeY;
	
		USceneCaptureComponent2D* capture = Cast<USceneCaptureComponent2D>(player->GetComponentByClass(USceneCaptureComponent2D::StaticClass()));		
		ssView.Capture = capture;

		views.Add(ssView);
	
		//save the canvas size so we can detect when it changes
		BuiltCanvasSize = CanvasSize;		

		UE_LOG(LogTemp, Log, TEXT("Allocated Viewport %d. Origin: (%f,%f) Size: (%f,%f)"), i, ssView.Origin.X, ssView.Origin.Y, ssView.Size.X, ssView.Size.Y);	
	}

	// TODO, Order viewports so they are consistent with the Launcher
	
	BuiltPlayers = players.Num();
	BuiltCanvasSize = CanvasSize;	

	return views;
}

bool UZLSplitScreenWidget::DoesNeedRebuild()
{
	//Has the number of players changed
	TArray<APawn*> players;
	FindSplitScreenPawns(players);

	if (players.Num() != BuiltPlayers) return true;
	
	// Resolution of the canvas change
	if (Canvas)
	{
		FVector2D currentCanvasLocalSize = Canvas->GetCachedGeometry().GetLocalSize();
		if (currentCanvasLocalSize.X != BuiltCanvasSize.X) return true;
		if (currentCanvasLocalSize.Y != BuiltCanvasSize.Y) return true;
	}

	//nothing changed.
	return false;
}


void UZLSplitScreenWidget::FindSplitScreenPawns(TArray<APawn*> &OutPawns)
{
	TArray<AActor*> foundPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerPawnClass, foundPlayers);

	for (auto& player : foundPlayers)
	{
		USceneCaptureComponent2D* capture = Cast<USceneCaptureComponent2D>(player->GetComponentByClass(USceneCaptureComponent2D::StaticClass()));
		if (capture)
		{
			OutPawns.Add(Cast <APawn>(player));
		}
	}
}
