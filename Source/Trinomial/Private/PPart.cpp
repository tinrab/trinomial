#include "PPart.h"
#include "ProceduralMeshComponent.h"

APPart::APPart()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent->SetMobility(EComponentMobility::Stationary);

	MeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetMobility(EComponentMobility::Stationary);
	MeshComponent->bUseAsyncCooking = true;
	MeshComponent->SetCollisionProfileName("NoCollision");
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetRelativeLocation(FVector::ZeroVector);
}

void APPart::BuildMesh() {}

#if WITH_EDITOR

void APPart::PostActorCreated()
{
	Super::PostActorCreated();
	BuildMesh();
}

void APPart::PostLoad()
{
	Super::PostLoad();
	BuildMesh();
}

void APPart::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	Super::PostEditChangeProperty(e);
	BuildMesh();
}

#endif
