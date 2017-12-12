#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PPart.h"
#include "PGravityManager.generated.h"

/**
 * Data about gravity
 */
struct FCalculateGravityResult
{
	/** Position of the closest point */
	FVector FloorPoint;

	/** Direction of the gravity */
	FVector Direction;
};


UCLASS()
class TRINOMIAL_API APGravityManager : public AActor
{
	GENERATED_BODY()

public:
	APGravityManager();

	/** Calculates gravity at point */
	FCalculateGravityResult CalculateGravity(FVector Point);

private:
	virtual void BeginPlay() override;

	/** All parts of the structure */
	UPROPERTY(EditAnywhere)
	TArray<APPart*> Parts;
};
