// Fill out your copyright notice in the Description page of Project Settings.
#include "SWeapon.h"
#include "CoopGame.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "TimerManager.h"

// Debugging weapon/projectile drawing lines 
static int32 DebugWeaponDrawing;
FAutoConsoleVariableRef CVARDebugWeaponDrawing(TEXT("COOP.DebugWeapons"), DebugWeaponDrawing, TEXT("Draw Debug Lines"), ECVF_Cheat);

// Sets default values
ASWeapon::ASWeapon()
{
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	MuzzleSocketName = "MuzzleSocket";
	BaseDamage = 20.0f;
	RateOfFire = 600;
}



void ASWeapon::Fire()
{
	GetWorld()->TimeSeconds;

	AActor* myOwner = GetOwner();

	if (!myOwner) return;

	FVector EyeLocation;
	FRotator EyeRotation;

	myOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * 10000);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(myOwner);
	QueryParams.AddIgnoredActor(this);
	QueryParams.bReturnPhysicalMaterial = true;
	QueryParams.bTraceComplex = true;

	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_GameTraceChannel1, QueryParams))
	{
		AActor* HitActor = Hit.GetActor();
				
		EPhysicalSurface SurfaceType = UPhysicalMaterial::DetermineSurfaceType(Hit.PhysMaterial.Get());

		UParticleSystem* SelectedEffect = nullptr;
		
		switch (SurfaceType)
		{
		case SURFACE_FLESHDEFAULT:
		case SURFACE_VENERAUBLE:
			SelectedEffect = FleshImpactEffect;
			break;
		default:
			SelectedEffect = DefaultImpactEffect;
		}

		if (SelectedEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SelectedEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
		}

		float ActualDamage = BaseDamage;

		if (SurfaceType == SURFACE_VENERAUBLE)
		{
			ActualDamage *= 4;
		}

		UGameplayStatics::ApplyPointDamage(HitActor, ActualDamage, EyeRotation.Vector(), Hit, myOwner->GetInstigatorController(), this, DamageType);
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

void ASWeapon::StartFire()
{	
	
	float timeBetweenShots = 60 / RateOfFire;
	float firstDelay = FMath::Max(LastFireTime + timeBetweenShots - GetWorld()->TimeSeconds,0.0f);

	GetWorld()->GetTimerManager().SetTimer(TimarHandle_TimeBetweenShots, this, &ASWeapon::Fire, timeBetweenShots, true, firstDelay);
	Fire();
}

void ASWeapon::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(TimarHandle_TimeBetweenShots);
}


