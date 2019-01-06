// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameState.h"




void AFPSGameState::MulticastOnMissionComplete_Implementation(APawn* Pawn, bool bMissionSuccess)
{
	
	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; It++)
	{
		if (Pawn && Pawn->IsLocallyControlled())
		{
			Pawn->DisableInput(nullptr);
		}
	}
	
}