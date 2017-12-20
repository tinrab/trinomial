#include "PGravityManager.h"
#include "Engine/World.h"
#include "UObject/UObjectIterator.h"
#include "PPart.h"
#include "PCubePart.h"
#include "Components/BoxComponent.h"

APGravityManager* APGravityManager::Singleton;

APGravityManager::APGravityManager()
{
	Singleton = this;
	PrimaryActorTick.bCanEverTick = false;
}

void APGravityManager::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	for (TObjectIterator<APPart> It; It; ++It)
	{
		if (It->GetWorld() == World)
		{
			Parts.Add(*It);
		}
	}
}

FCalculateGravityResult APGravityManager::CalculateGravity(FVector Point)
{
	FCalculateGravityResult Result;
	Result.Distance = TNumericLimits<float>::Max();

	for (APPart* Part : Singleton->Parts)
	{
		check(Part);
		FVector ClosestPoint;

		// Cube part
		if (Part->IsA<APCubePart>())
		{
			APCubePart* CubePart = Cast<APCubePart>(Part);
			CubePart->GetBoxComponent()->GetClosestPointOnCollision(Point, ClosestPoint);
		}

		// Check if it's the closest
		float Distance = FVector::Distance(ClosestPoint, Point);
		if (Distance < Result.Distance)
		{
			Result.Distance = Distance;
			Result.Part = Part;
			Result.FloorPoint = ClosestPoint;
		}
	}

	Result.Direction = (Result.FloorPoint - Point).GetSafeNormal();

	return Result;
}
