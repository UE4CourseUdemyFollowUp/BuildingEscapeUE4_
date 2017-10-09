// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Classes/Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "DoorOpener.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPEUE4_API UDoorOpener : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpener();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float GetTotalMassOfActorsOnPlate();

public:
	UPROPERTY(BlueprintAssignable)
	FOnDoorRequest OnOpenDoor;

	UPROPERTY(BlueprintAssignable)
	FOnDoorRequest OnCloseDoor;

private:	
	AActor* TheDoor;

	UPROPERTY(EditAnywhere)
	float TriggerMass;

	UPROPERTY(EditAnywhere)
	ATriggerVolume *PressurePlate;
};
