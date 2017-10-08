// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorOpener.h"
#include <string>

#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformMath.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"




// Sets default values for this component's properties
UDoorOpener::UDoorOpener()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();

	TheDoor = GetOwner();
	// ...
	if (!TheDoor)
		return;

	InitialYaw = TheDoor->GetActorRotation().Yaw;
	UE_LOG(LogTemp, Warning, TEXT("Initial rotation is: %s"), *TheDoor->GetActorRotation().ToCompactString());
}


// Called every frame
void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate)
	{
		if (!bIsDoorOpening && GetTotalMassOfActorsOnPlate() > 50.f)
		{
			UE_LOG(LogTemp, Warning, TEXT("Open the door"));
			bIsDoorOpening = true;
		}
		else if (bIsDoorOpening && GetTotalMassOfActorsOnPlate() < 50.f)
		{
			UE_LOG(LogTemp, Warning, TEXT("Close the door"));
			bIsDoorOpening = false;
		}
	}

	RunTheDoor(DeltaTime);
}

void UDoorOpener::RunTheDoor(float DeltaTime)
{
	if (!TheDoor)
		return;

	// Current rotation of the door and Yaw of the door what we want to reach
	FRotator CurrentRot = TheDoor->GetActorRotation(); 
	float TargetYaw = InitialYaw + OpenAngleLimit;

	// Get rid of negative 180 angles. 'false' means we're not doing there anything
	CurrentRot.Yaw < 0 ? CurrentRot.Yaw += 360.f : false ;

	// Tick rotation
	FRotator DiffRot(0.f, 0.f, 0.f);

	// Limits of rotation
	if (bIsDoorOpening && CurrentRot.Yaw > TargetYaw)
	{
		CurrentRot.Yaw = TargetYaw;
	}
	else if (!bIsDoorOpening && CurrentRot.Yaw < InitialYaw)
	{
		CurrentRot.Yaw = InitialYaw;
	}
	else
	{
		// Calculate Tick rotation according to moving direction
		DiffRot.Yaw = DeltaTime * Speed * (bIsDoorOpening ? 1 : -1);

		// Apply rotation difference to the actor
		TheDoor->AddActorLocalRotation(DiffRot);
	}
}

float UDoorOpener::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;
	if (PressurePlate)
	{
		PressurePlate->GetOverlappingActors(OverlappingActors);

		for (auto& Actor : OverlappingActors)
		{
			TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}
	}

	return TotalMass;
}

