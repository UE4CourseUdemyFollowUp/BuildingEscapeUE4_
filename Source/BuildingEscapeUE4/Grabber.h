// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

class UPhysicsHandleComponent;
class UInputComponent;

USTRUCT()
struct FViewLine
{
	GENERATED_BODY()

	UPROPERTY()
	FVector ViewLineStart;

	UPROPERTY()
	FVector ViewLineEnd;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPEUE4_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	

private:
	void Grab();
	void Release();

	bool CheckPhysicsHandleComponent();
	bool SetupInputComponent();

	FHitResult GetFirstHitPhysicsBody() const;

	FViewLine GetViewLine() const;

private:

	// Length of grabber "hands"
	UPROPERTY(EditAnywhere)
	float HandLength = 100.f;

	UPhysicsHandleComponent* PhysicsHandle;

	UInputComponent* InputComponent;
};
