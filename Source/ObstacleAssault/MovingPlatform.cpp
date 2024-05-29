// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// Store the starting location
	StartLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	// Current Location
	FVector CurrentLocation = GetActorLocation();
	// Increment location
	CurrentLocation += (Speed * DeltaTime);
	// Set new location
	SetActorLocation(CurrentLocation);

	// Calculate distance
	float Distance = FVector::Distance(StartLocation, CurrentLocation);

	if (Distance > MaximumDistance)
	{
		float MovedDistance = Distance - MaximumDistance;

		FString Name = GetName();
		UE_LOG(LogTemp, Display, TEXT("%s Overshoot by %f"), *Name, MovedDistance);

		FVector MoveDirection = Speed.GetSafeNormal();

		// Setting current location
		StartLocation = StartLocation + MoveDirection * Distance;

		SetActorLocation(StartLocation);

		// Reverse direction
		Speed = -Speed;
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationSpeed * DeltaTime);
}