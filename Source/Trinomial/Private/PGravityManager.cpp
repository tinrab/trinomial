#include "PGravityManager.h"
#include "Engine/World.h"
#include "UObject/UObjectIterator.h"
#include "PPart.h"

APGravityManager::APGravityManager()
{
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
	return FCalculateGravityResult();
}
