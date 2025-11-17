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

	StartLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move Platform Forwards
		// Get Current Location
	FVector CurrentLocation = GetActorLocation();
		// Add Vector to that Location
	CurrentLocation = CurrentLocation + PlatformVelocity * DeltaTime;
		// Set Actor Location
	SetActorLocation(CurrentLocation);
	// Send Platform back if gone too far
		DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);
		// check how far we've moved
		// reverse direction of motion if gone too far

	// 프레임마다 델타타임이 달라서 DistanceMoved가 MoveDistance에 딱 맞게 떨어지질 않음.
	/*
	예시:

MoveDistance = 500

프레임당 이동 = 17

29프레임 → 493

30프레임 → 510 (훅 넘음)

즉, 플랫폼이 500을 넘어서 씩 지나친 후에 반전이 일어남.
	*/
	if (DistanceMoved > MoveDistance) {
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
/*이렇게 하면 이동이 경계를 넘었더라도

딱 MoveDistance 위치로 끌어와서 정확히 맞춤

오버슈팅된 위치(CurrentLocation)를 그대로 StartLocation으로 쓰는 게 아니라, 원래 StartLocation + 정확한 MoveDistance만큼 이동한 지점
*/
}

