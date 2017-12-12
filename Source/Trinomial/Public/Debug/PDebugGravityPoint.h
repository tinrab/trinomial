#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PDebugGravityPoint.generated.h"

UCLASS()
class TRINOMIAL_API APDebugGravityPoint : public AActor
{
	GENERATED_BODY()

public:
	APDebugGravityPoint();

private:
	virtual void Tick(float DeltaTime) override;
};
