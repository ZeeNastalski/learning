// Fill out your copyright notice in the Description page of Project Settings.


#include "SWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

// Debugging weapon/projectile drawing lines 
static int32 DebugWeaponDrawing;
FAutoConsoleVariableRef CVARDebugWeaponDrawing(TEXT("COOP.DebugWeapons"), DebugWeaponDrawing, TEXT("Draw Debug Lines"), ECVF_Cheat);

// Sets default values
ASWeapon::ASWeapon()
{

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	MuzzleSocketName = "MuzzleSocket";
}



void ASWeapon::Fire()
{
	AActor* myOwner = GetOwner();

	if (!myOwner) return;

	FVector EyeLocation;
	FRotator EyeRotation;

	myOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * 10000);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(myOwner);
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;

	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams))
	{
		AActor* HitActor = Hit.GetActor();
		UGameplayStatics::ApplyPointDamage(HitActor, 20.0f, EyeRotation.Vector(), Hit, myOwner->GetInstigatorController(), this, DamageType);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	}

	
	if (DebugWeaponDrawing > 0)
	{
		DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::White, false, 1.0f, 0, 1.0f);
	}
	

	if(MuzzleEffect)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MeshComp, MuzzleSocketName);
	}

	if (BeamEffect)
	{
		UParticleSystemComponent* beam = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(), 
			BeamEffect, 
			MeshComp->GetSocketLocation(MuzzleSocketName));

		if (beam)
		{
			AActor* HitActor = Hit.GetActor();
			if (HitActor)
			{
				beam->SetVectorParameter("Target", Hit.ImpactPoint);
			}
			else
			{
				beam->SetVectorParameter("Target", TraceEnd);
			}
		}
	}

	APawn* MyOwner = Cast<APawn>(GetOwner());
	if (MyOwner)
	{
		APlayerController* PC = Cast<APlayerController>(MyOwner->GetController());
		if (PC)
		{
			PC->ClientPlayCameraShake(CameraShakeType);
		}
	}

}


