// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ZLSplitScreenWidget.generated.h"

/**
 * 
 */

class UCanvasPanel;
UCLASS()
class FPSGAME_API UZLSplitScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:	
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void RebuildSplitScreen();
	virtual bool DoesNeedRebuild();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SplitScreen")
	UCanvasPanel* Canvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SplitScreen")
	int Players;

protected:
	FVector2D BuiltCanvasSize;
	int BuiltPlayers;

};
