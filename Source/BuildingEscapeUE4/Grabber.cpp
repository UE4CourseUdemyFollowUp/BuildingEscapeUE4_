// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	FVector PViewLocation;
	FRotator PViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PViewLocation, PViewRotation);

	FVector ViewEndPoint = PViewLocation + PViewRotation.Vector() * Reach;
	
	DrawDebugLine(GetWorld(), PViewLocation, ViewEndPoint, FColor(255, 0, 0), false, -1.f, 2.f);

	FCollisionQueryParams CollisionQueryParams(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(
		Hit, 
		PViewLocation, 
		ViewEndPoint, 
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), 
		CollisionQueryParams);
	
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabber detects: %s"), *(ActorHit->GetName()));
	}
}

