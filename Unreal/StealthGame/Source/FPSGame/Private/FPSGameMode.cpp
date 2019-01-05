// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}


void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool bMissionSuccess)
{
	if (InstigatorPawn)
	{		
		InstigatorPawn->DisableInput(nullptr);

		TArray<AActor*> viewpoints;
		UGameplayStatics::GetAllActorsOfClass(this, this->SpectatingViewPoint, viewpoints);

		APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());

		if (viewpoints.Num() > 0 && PC)
		{
			FViewTargetTransitionParams params;
			params.BlendTime = 0.5f;
			
			PC->SetViewTargetWithBlend(viewpoints[0], 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
		}

	}


	OnMissionCompleted(InstigatorPawn, bMissionSuccess);



}
