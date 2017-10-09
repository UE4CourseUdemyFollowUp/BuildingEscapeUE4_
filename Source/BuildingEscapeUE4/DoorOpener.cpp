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

	UE_LOG(LogTemp, Warning, TEXT("Initial rotation is: %s"), *TheDoor->GetActorRotation().ToCompactString());
}


// Called every frame
void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate)
	{
		if (GetTotalMassOfActorsOnPlate() > TriggerMass)
		{
			UE_LOG(LogTemp, Warning, TEXT("Open the door"));
			OnOpenDoor.Broadcast();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Close the door"));
			OnCloseDoor.Broadcast();
		}
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

