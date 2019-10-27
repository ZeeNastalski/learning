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
		SplitscreenInfo.Add(FSplitscreenData());
	}
	//No players - still full screen
	SplitscreenInfo[0].PlayerData.Add(FPerPlayerSplitscreenData(1.0f, 1.0f, 0.0f, 0.0f)); //Size X, Size Y, Origin X, Origin Y
	
	//One player
	SplitscreenInfo[1].PlayerData.Add(FPerPlayerSplitscreenData(1.0f, 1.0f, 0.0f, 0.0f));
	
	//Two players
	SplitscreenInfo[2].PlayerData.Add(FPerPlayerSplitscreenData(1.0f, 0.5f, 0.0f, 0.0f)); //Top Row
	SplitscreenInfo[2].PlayerData.Add(FPerPlayerSplitscreenData(1.0f, 0.5f, 0.0f, 0.5f)); //Bottom Row
	
	//Three players
	SplitscreenInfo[3].PlayerData.Add(FPerPlayerSplitscreenData(0.5f, 0.5f, 0.0f, 0.0f)); //Top Row
	SplitscreenInfo[3].PlayerData.Add(FPerPlayerSplitscreenData(0.5f, 0.5f, 0.5f, 0.0f)); //Top Row
	SplitscreenInfo[3].PlayerData.Add(FPerPlayerSplitscreenData(1.0f, 0.5f, 0.0f, 0.5f)); //Bottom Row
	
	//Four players
	SplitscreenInfo[4].PlayerData.Add(FPerPlayerSplitscreenData(0.5f, 0.5f, 0.0f, 0.0f)); //Top Row
	SplitscreenInfo[4].PlayerData.Add(FPerPlayerSplitscreenData(0.5f, 0.5f, 0.5f, 0.0f)); //Top Row
	SplitscreenInfo[4].PlayerData.Add(FPerPlayerSplitscreenData(0.5f, 0.5f, 0.0f, 0.5f)); //Bottom Row
	SplitscreenInfo[4].PlayerData.Add(FPerPlayerSplitscreenData(0.5f, 0.5f, 0.5f, 0.5f)); //Bottom Row

	//Five players
	SplitscreenInfo[5].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 0.0f, 0.0f)); //Top Row
	SplitscreenInfo[5].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 1.f / 3.f, 0.0f)); //Top Row
	SplitscreenInfo[5].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 2.f / 3.f, 0.0f)); //Top Row
	SplitscreenInfo[5].PlayerData.Add(FPerPlayerSplitscreenData(0.5, 0.5f, 0.0f, 0.5f)); //Bottom Row
	SplitscreenInfo[5].PlayerData.Add(FPerPlayerSplitscreenData(0.5, 0.5f, 0.5f, 0.5f)); //Bottom Row

	//Six players
	SplitscreenInfo[6].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 0.0f, 0.0f)); //Top Row
	SplitscreenInfo[6].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 1.f / 3.f, 0.0f)); //Top Row
	SplitscreenInfo[6].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 2.f / 3.f, 0.0f)); //Top Row
	SplitscreenInfo[6].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 0.0f, 0.5f)); //Bottom Row
	SplitscreenInfo[6].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 1.f / 3.f, 0.5f)); //Bottom Row
	SplitscreenInfo[6].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 2.f / 3.f, 0.5f)); //Bottom Row

	//Seven players
	SplitscreenInfo[7].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.0f, 0.0f)); //Top Row
	SplitscreenInfo[7].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.25f, 0.0f)); //Top Row
	SplitscreenInfo[7].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.5f, 0.0f)); //Top Row
	SplitscreenInfo[7].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.75f, 0.0f)); //Top Row
	SplitscreenInfo[7].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 0.0f, 0.5f)); //Bottom Row
	SplitscreenInfo[7].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 1.f / 3.f, 0.5f)); //Bottom Row
	SplitscreenInfo[7].PlayerData.Add(FPerPlayerSplitscreenData(1.f / 3.f, 0.5f, 2.f / 3.f, 0.5f)); //Bottom Row

	//Eight players
	SplitscreenInfo[8].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.0f, 0.0f)); //Top Row
	SplitscreenInfo[8].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.25f, 0.0f)); //Top Row
	SplitscreenInfo[8].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.5f, 0.0f)); //Top Row
	SplitscreenInfo[8].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.75f, 0.0f)); //Top Row
	SplitscreenInfo[8].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.0f, 0.5f)); //Bottom Row
	SplitscreenInfo[8].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.25f, 0.5f)); //Bottom Row
	SplitscreenInfo[8].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.5f, 0.5f)); //Bottom Row
	SplitscreenInfo[8].PlayerData.Add(FPerPlayerSplitscreenData(0.25f, 0.5f, 0.75f, 0.5f)); //Bottom Row


	// Call the Blueprint "Event Construct" node
	Super::NativeConstruct();
}


void UZLSplitScreenWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{	
	Super::NativeTick(MyGeometry, InDeltaTime);


	/*
	if (Canvas && DoesNeedRebuild())
	{
		RebuildSplitScreen();
	}
	*/
}

TArray<FSplitScreenView> UZLSplitScreenWidget::RebuildSplitScreen()
{
	UE_LOG(LogTemp, Log, TEXT("Rebuilding Split Screen"));

	TArray<FSplitScreenView> views;

	// The blueprint didn't assign the canvas yet
	if (!Canvas) return views;

	// The blueprint didn't assign the images
	if (ViewportImages.Num()==0) return views;
	
	// clear everything first
	for (auto& image : ViewportImages)
	{	/*
		image->SetBrushFromMaterial(nullptr);
		image->SetBrushSize(FVector2D(0, 0));

		UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(image->Slot);
		slot->SetPosition(FVector2D(0, 0));
		*/
	}

	FVector2D CanvasSize = Canvas->GetCachedGeometry().GetAbsoluteSize();
		
	// find all scene capture 2d in pawns
	TArray<APawn*> players;
	FindSplitScreenPawns(players);
	UE_LOG(LogTemp, Log, TEXT("Split screen canvas dimension %f x %f, players: %d"), CanvasSize.X, CanvasSize.Y, players.Num());

	int PlayerCount = players.Num();

	for(int i = 0; i<PlayerCount; i++)
	{
		APawn* player = players[i];
				
		FSplitScreenView ssView;
		ssView.Origin.X = CanvasSize.X * SplitscreenInfo[PlayerCount].PlayerData[i].OriginX;
		ssView.Origin.Y = CanvasSize.Y * SplitscreenInfo[PlayerCount].PlayerData[i].OriginY;
		ssView.Size.X = CanvasSize.X * SplitscreenInfo[PlayerCount].PlayerData[i].SizeX;
		ssView.Size.Y = CanvasSize.Y * SplitscreenInfo[PlayerCount].PlayerData[i].SizeY;

		UImage* image = ViewportImages[i];

		/*
		// Get SceneCaputre2D from player (this should be part of ZL player interface)
		USceneCaptureComponent2D* capture = Cast<USceneCaptureComponent2D>(player->GetComponentByClass(USceneCaptureComponent2D::StaticClass()));
		
		//Create render target
		UTextureRenderTarget2D* rendTarget = UKismetRenderingLibrary::CreateRenderTarget2D(
			GetWorld(), 
			FMath::CeilToInt(ssView.Size.X), 
			FMath::CeilToInt(ssView.Size.Y), 
			ETextureRenderTargetFormat::RTF_RGBA16f);

		// Create material instance
		UMaterialInstanceDynamic* ViewportMaterialInstance = UMaterialInstanceDynamic::Create(RenderMaterial, this);

		
		// Set render target as a texture for the material instance
		ViewportMaterialInstance->SetTextureParameterValue("Texture", rendTarget);

		// Pass material to the caller
		ssView.ViewportMaterial = ViewportMaterialInstance;

		views.Add(ssView);

		

		image->SetBrushFromMaterial(ViewportMaterialInstance);
		
		image->SetBrushSize(ssView.Size);
		*/

		UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(image->Slot);
		slot->SetPosition(ssView.Origin);

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
		FVector2D currentCanvasLocalSize = Canvas->GetCachedGeometry().GetAbsoluteSize();
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
