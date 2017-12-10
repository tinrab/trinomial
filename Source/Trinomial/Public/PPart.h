#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PPart.generated.h"

class UStaticMeshComponent;

UCLASS(Abstract)
class TRINOMIAL_API APPart : public AActor
{
	GENERATED_BODY()

	APPart();

protected:

	/** Mesh for the part */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;
};
