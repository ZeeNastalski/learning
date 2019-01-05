// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSLaunchPad.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "FPSCharacter.h"


// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	RootComponent = CollisionComp;

	CollisionComp->SetBoxExtent(FVector(100.0f));
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));

	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	
	
	MeshComp->SetupAttachment(CollisionComp);

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchPad::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AFPSLaunchPad::BeginPlay()
{
	Super::BeginPlay();	
}

void AFPSLaunchPad::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Overlapped with launch pad"));
	AFPSCharacter* Player = Cast<AFPSCharacter>(OtherActor);
	FVector fwd = GetActorForwardVector();
	FVector up = GetActorUpVector();

	FVector launch = fwd + up;
	launch.Normalize();

	if (Player) 
	{
		Player->LaunchCharacter(launch *LaunchForce, true, true);
	}
}



