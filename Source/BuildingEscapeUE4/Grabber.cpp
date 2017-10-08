// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsHandleComponent.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
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

	CheckPhysicsHandleComponent();
	SetupInputComponent();
	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PhysicsHandle)
		return;

	if (PhysicsHandle->GrabbedComponent)
	{
		FViewLine ViewLine = GetViewLine();

		PhysicsHandle->SetTargetLocation(ViewLine.ViewLineEnd);
	}

}

void UGrabber::Grab()
{
	FHitResult HitResult = GetFirstHitPhysicsBody();
	auto ComponentToGrab = HitResult.GetComponent();
	AActor* ActorHit = HitResult.GetActor();
	if (!ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabber doesn't hit anything"));
		return;
	}
	if (PhysicsHandle)
	{
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			false);
	}

}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber releases"));
	if(PhysicsHandle)
		PhysicsHandle->ReleaseComponent();
}

bool UGrabber::CheckPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing PhysicHandleComponent!"), *GetName());
		return false;
	}
	return true;
}

bool UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input Component found and ready"));
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);

		return true;
	}
	return false;
}

FHitResult UGrabber::GetFirstHitPhysicsBody() const
{
	FViewLine ViewLine = GetViewLine();

	FCollisionQueryParams CollisionQueryParams(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		ViewLine.ViewLineStart,
		ViewLine.ViewLineEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		CollisionQueryParams);

	return Hit;
}

FViewLine UGrabber::GetViewLine() const
{
	FViewLine ViewLine;

	FRotator PViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(ViewLine.ViewLineStart, PViewRotation);

	ViewLine.ViewLineEnd = ViewLine.ViewLineStart + PViewRotation.Vector() * HandLength;

	return ViewLine;
}

