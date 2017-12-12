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

	UWorld* World = GetWorld();
	FVector Location = GetActorLocation();
	FCalculateGravityResult Gravity = APGravityManager::CalculateGravity(Location);

	DrawDebugSphere(World, Location, 25.0f, 16, FColor::Red);
	DrawDebugLine(World, Location, Gravity.FloorPoint, FColor::Red);
}
