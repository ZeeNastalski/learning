// Fill out your copyright notice in the Description page of Project Settings.

#include "ZLSplitScreenWidget.h"
#include "Components/CanvasPanel.h"


void UZLSplitScreenWidget::NativeConstruct()
{
	// Call the Blueprint "Event Construct" node
	Super::NativeConstruct();
}


void UZLSplitScreenWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{	
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (Canvas && DoesNeedRebuild())
	{
		RebuildSplitScreen();
	}	
}

void UZLSplitScreenWidget::RebuildSplitScreen()
{
	if (!Canvas) return;
	
	//clear everything first
	Canvas->ClearChildren();
	FVector2D CanvasSize = Canvas->GetCachedGeometry().GetLocalSize();
	
	//position viewpoorts

	BuiltPlayers = Players;
	BuiltCanvasSize = CanvasSize;	
}

bool UZLSplitScreenWidget::DoesNeedRebuild()
{
	//Has the number of players changed
	if (Players != BuiltPlayers) return true;
	
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
