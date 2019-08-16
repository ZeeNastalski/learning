// Fill out your copyright notice in the Description page of Project Settings.


#include "SLauncher.h"
#include "Components/SkeletalMeshComponent.h"
#include "SProjectile.h"
#include "Kismet/GameplayStatics.h"

void ASLauncher::Fire()
{
	//Super::Fire();
	
	AActor* myOwner = GetOwner();

	if (!myOwner) return;


	if (MuzzleEffect)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MeshComp, MuzzleSocketName);
	}

	if (ProjectileClass)
	{
		FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);

		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.Instigator = myOwner->GetInstigator();

		FVector EyeLocation;
		FRotator EyeRotation;

		myOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		//TODO: Consider changing to AdjustIfPossibleButAlwaysSpawn. Currently if player is close to wall the projectile shouldn't spawn
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		GetWorld()->SpawnActor<ASProjectile>(ProjectileClass, MuzzleLocation, EyeRotation, ActorSpawnParams);
	}

}
