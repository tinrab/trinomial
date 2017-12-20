#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PPart.generated.h"

class UProceduralMeshComponent;

UCLASS()
class TRINOMIAL_API APPart : public AActor
{
	GENERATED_BODY()

public:
	APPart();

#if WITH_EDITOR
	void PostActorCreated() override;
	void PostLoad() override;
	void PostEditChangeProperty(struct FPropertyChangedEvent&) override;
#endif

protected:
	/** Mesh for this part */
	UPROPERTY(VisibleDefaultsOnly)
	UProceduralMeshComponent* MeshComponent;

	/** Material for the generated mesh */
	UPROPERTY(EditAnywhere, Category = "Part")
	UMaterialInterface* Material;

	/** Builds procedural mesh for this part */
	virtual void BuildMesh();
};
