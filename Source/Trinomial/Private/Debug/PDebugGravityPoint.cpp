#include "PDebugGravityPoint.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PGravityManager.h"

APDebugGravityPoint::APDebugGravityPoint()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APDebugGravityPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*
	UWorld* World = GetWorld();
	FVector Location = GetActorLocation();
	FCalculateGravityResult Gravity = 
	DrawDebugSphere(World, GetActorLocation(), 100.0f, 32, FColor::Red);
	*/
}
