// Fill out your copyright notice in the Description page of Project Settings.

#include "TestActor.h"
#include "ZLTelemetry.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"


// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	
	FPerson Person;

	Person.Age = 38;
	Person.occupation = "Developer";
	Person.Name = "Zbigniew";
	Person.pos.X = 1.0f;
	Person.pos.Y = 2.0f;
	Person.pos.Z = 3.0f;
	Person.rot = GetActorRotation();
		
	UZLTelemetry::LogTelemetryEvent(Person);
}



// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}





