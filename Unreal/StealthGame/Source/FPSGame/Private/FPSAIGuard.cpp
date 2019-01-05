// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"
#include "DrawDebugHelpers.h"
#include "Perception/PawnSensingComponent.h"
#include "FPSGameMode.h"
#include "Net/UnrealNetwork.h"


// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->OnSeePawn.AddDynamic(this,&AFPSAIGuard::OnSeePawn);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);

	GuardState = EAIState::Idle;

	SetReplicates(true);
}

void AFPSAIGuard::OnSeePawn(APawn * SeenPawn)
{
	
	if (SeenPawn == nullptr)
	{
		return;
	}

	AFPSGameMode* GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		GM->CompleteMission(SeenPawn, false);
	}

	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);

	SetGuardState(EAIState::Alerted);
}

void AFPSAIGuard::OnNoiseHeard(APawn * InstigatorActor, const FVector & Location, float Volume)
{
	if (GuardState == EAIState::Alerted) 
	{
		return;
	}

	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 10.0f);

	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0.0f;
	NewLookAt.Roll = 0.0f;
	SetActorRotation(NewLookAt);

	GetWorldTimerManager().ClearTimer(TimerHandle_ResetRotation);	
	GetWorldTimerManager().SetTimer(TimerHandle_ResetRotation, this, &AFPSAIGuard::ResetOrienation, 3.0f);


	SetGuardState(EAIState::Suspicious);
	
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	OriginalRotation = GetActorRotation();
	
}

void AFPSAIGuard::OnRep_GuardState()
{
	OnStateChanged(GuardState);
}


void AFPSAIGuard::SetGuardState(EAIState NewState)
{
	if (NewState == GuardState)
	{
		return;
	}

	GuardState = NewState;
	OnRep_GuardState();
}

void AFPSAIGuard::ResetOrienation()
{
	if (GuardState == EAIState::Alerted)
	{
		return;
	}

	SetActorRotation(OriginalRotation);
	SetGuardState(EAIState::Idle);
}



// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPSAIGuard::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFPSAIGuard, GuardState);
}


