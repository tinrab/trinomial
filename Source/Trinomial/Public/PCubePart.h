#pragma once

#include "CoreMinimal.h"
#include "PPart.h"
#include "PCubePart.generated.h"

class UBoxComponent;

UCLASS()
class TRINOMIAL_API APCubePart : public APPart
{
	GENERATED_BODY()

public:
	APCubePart();

	/** Returns size of the cube */
	FORCEINLINE FIntVector GetCubeSize() const { return CubeSize; };

	/** Sets the size of a cube in part units */
	FORCEINLINE void SetCubeSize(FIntVector InCubeSize) { CubeSize = InCubeSize; };

	/** Returns box component */
	FORCEINLINE UBoxComponent* GetBoxComponent() const { return BoxComponent; }

protected:
	void BuildMesh() override;

private:
	/** Size of the cube */
	UPROPERTY(EditAnywhere, Category = "Part")
	FIntVector CubeSize;

	/** Box collision component */
	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent* BoxComponent;
};
