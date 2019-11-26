// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ZLSplitScreenWidget.generated.h"

class UCanvasPanel;
class UImage;

USTRUCT(BlueprintType)
struct FPSGAME_API FSplitScreenView
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "SplitScreen")
	FVector2D Origin;

	UPROPERTY(BlueprintReadWrite, Category = "SplitScreen")
	FVector2D Size;	

	UPROPERTY(BlueprintReadWrite, Category = "SplitScreen")
	USceneCaptureComponent2D* Capture;
};


/**
 * 
 */
UCLASS()
class FPSGAME_API UZLSplitScreenWidget : public UUserWidget
{
	
	GENERATED_BODY()

public:	
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category="SplitScreen")
	virtual TArray<FSplitScreenView> RebuildSplitScreen();
	
	UFUNCTION(BlueprintCallable, Category="SplitScreen")
	virtual bool DoesNeedRebuild();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SplitScreen")
	UCanvasPanel* Canvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SplitScreen")
	TSubclassOf<APawn> PlayerPawnClass;

protected:
	void FindSplitScreenPawns(TArray<APawn*>& OutPawns);
	TArray<struct FSplitscreenData> SplitScreenLookup;
	
	FVector2D BuiltCanvasSize;
	int BuiltPlayers;
};
