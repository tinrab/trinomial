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

	/** Distance to floor */
	float Distance;

	/** Floor part */
	TWeakObjectPtr<class APPart> Part;

	FCalculateGravityResult()
	{
		FMemory::Memzero(this, sizeof(FCalculateGravityResult));
	}

	/** Whether result has been assigned */
	FORCEINLINE bool IsValid() const { return Part.IsValid(); }
};

UCLASS()
class TRINOMIAL_API APGravityManager : public AActor
{
	GENERATED_BODY()

public:
	APGravityManager();

	/** Calculates gravity at point */
	static FCalculateGravityResult CalculateGravity(FVector Point);

private:
	static APGravityManager* Singleton;

	/** All parts of the structure */
	UPROPERTY(EditAnywhere)
	TArray<APPart*> Parts;

	virtual void BeginPlay() override;
};
