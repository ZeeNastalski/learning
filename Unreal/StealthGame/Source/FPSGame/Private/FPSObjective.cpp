// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSObjective.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"

// Sets default values
AFPSObjective::AFPSObjective()
{

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ZeeMeshComp"));
	RootComponent = MeshComp;

	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("ZeeSphereComp"));
	SphereComp->SetupAttachment(MeshComp);

	SphereComp->SetSphereRadius(128, false);

	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	SetReplicates(true);
}

// Called when the game starts or when spawned
void AFPSObjective::BeginPlay()
{
	Super::BeginPlay();
	PlayEffects();
}

void AFPSObjective::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());
}


void AFPSObjective::NotifyActorBeginOverlap(AActor * OtherActor)
{	
	Super::NotifyActorBeginOverlap(OtherActor);
	
	PlayEffects();
	

	if (Role == ROLE_Authority)
	{

		AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor);
		if (MyCharacter)
		{
			MyCharacter->bIsCarryingObjective = true;
			Destroy();
		}
	}
	
}

