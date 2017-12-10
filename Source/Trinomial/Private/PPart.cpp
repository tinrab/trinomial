#include "PPart.h"
#include "Components/StaticMeshComponent.h"

APPart::APPart()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionProfileName(TEXT("Part"));
	if (RootComponent == nullptr)
	{
		RootComponent = Mesh;
	} else
	{
		Mesh->SetupAttachment(RootComponent);
	}
}
