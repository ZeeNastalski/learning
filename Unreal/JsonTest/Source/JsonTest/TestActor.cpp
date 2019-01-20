// Fill out your copyright notice in the Description page of Project Settings.

#include "TestActor.h"
#include "ZLTelemetry.h"



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
		
	ATestActor::LogTelemetryEvent(Person);
}



// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

template<typename InStructType>
void ATestActor::LogTelemetryEvent(const InStructType& InStruct)
{
	FString InnerString;
	FString now = FDateTime::UtcNow().ToIso8601();

	FName typeName = InStruct.StaticStruct()->GetFName();

	FJsonObjectConverter::UStructToJsonObjectString(InStruct, InnerString, 0, 0, 0, nullptr, false);

	// Encapsulate inStruct in object named by the class name and add timestamp to the root
	FString jsonString = FString::Printf(TEXT("{\"@t\":\"%s\",\"%s\":%s}"), *now, *(typeName.ToString()), *InnerString);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *jsonString);
}



