#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PPart.h"
#include "PGravityManager.generated.h"

UCLASS()
class TRINOMIAL_API APGravityManager : public AActor
{
	GENERATED_BODY()
	
	APGravityManager();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TArray<APPart*> Parts;
};
