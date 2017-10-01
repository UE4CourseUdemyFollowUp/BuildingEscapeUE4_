// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReporterComponent.h"


// Sets default values for this component's properties
UPositionReporterComponent::UPositionReporterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReporterComponent::BeginPlay()
{
	Super::BeginPlay();

	FString ObjectName = GetOwner()->GetName();
	FVector ObjectPosition = GetOwner()->GetTransform().GetLocation();
	FString ObjectPosString = ObjectPosition.ToCompactString();
	UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *ObjectName, *ObjectPosString);
	
}


// Called every frame
void UPositionReporterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

