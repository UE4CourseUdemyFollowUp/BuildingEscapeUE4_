// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorOpener.h"

#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformMath.h"



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

	KeyActor = GetWorld()->GetFirstPlayerController()->GetPawn();

	TheDoor = GetOwner();
	Speed = 50.f;
	MaxAngle = 110.f;
	// ...
	TheDoor->SetActorRotation(FRotator(0.f, 110.f, 0.f));
}


// Called every frame
void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator CurrentRot = TheDoor->GetActorRotation();

	FRotator DiffRot(0.f, 0.f, 0.f);
	
	if (CurrentRot.Yaw >= MaxAngle)
	{
		UE_LOG(LogTemp, Warning, TEXT("Yaw > %s is at %s"), *(TheDoor->GetName()), *CurrentRot.ToCompactString());
		CurrentRot.Yaw = MaxAngle;
		bIsMovingForward = true;
	}
	else if (CurrentRot.Yaw <= -MaxAngle)
	{
		UE_LOG(LogTemp, Warning, TEXT("Yaw < %s is at %s"), *(TheDoor->GetName()), *CurrentRot.ToCompactString());
		CurrentRot.Yaw = -MaxAngle;
		bIsMovingForward = false;
	}

	DiffRot.Yaw = DeltaTime * Speed * (bIsMovingForward ? -1 : 1);

	//TheDoor->SetActorRotation(CurrentRot + DiffRot);
	// ...

	if (PressurePlate)
	{
		if (PressurePlate->IsOverlappingActor(KeyActor))
		{
			UE_LOG(LogTemp, Warning, TEXT("Open the door"));
		}
	}	
}

