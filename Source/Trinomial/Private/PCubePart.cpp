#include "PCubePart.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"
#include "Components/BoxComponent.h"

APCubePart::APCubePart()
{
	CubeSize = FIntVector(1, 1, 1);
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetMobility(EComponentMobility::Stationary);
	BoxComponent->SetCollisionProfileName(TEXT("Part"));
	BoxComponent->SetBoxExtent(FVector(CubeSize) * 200.0f);
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetRelativeLocation(FVector::ZeroVector);
}

void APCubePart::BuildMesh()
{
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FProcMeshTangent> Tangents;

	UKismetProceduralMeshLibrary::GenerateBoxMesh(FVector(CubeSize) * 200.0f, Vertices, Triangles, Normals, UVs, Tangents);

	// Create UVs
	UVs.Reset();
	UVs.AddUninitialized(Vertices.Num());
	// Z+
	UVs[0] = FVector2D(0.0f, 0.0f);
	UVs[1] = FVector2D(0.0f, CubeSize.X);
	UVs[2] = FVector2D(CubeSize.Y, CubeSize.X);
	UVs[3] = FVector2D(CubeSize.Y, 0.0f);
	// X-
	UVs[4] = FVector2D(0.0f, 0.0f);
	UVs[5] = FVector2D(0.0f, CubeSize.Z);
	UVs[6] = FVector2D(CubeSize.Y, CubeSize.Z);
	UVs[7] = FVector2D(CubeSize.Y, 0.0f);
	// Y+
	UVs[8] = FVector2D(0.0f, 0.0f);
	UVs[9] = FVector2D(0.0f, CubeSize.Z);
	UVs[10] = FVector2D(CubeSize.X, CubeSize.Z);
	UVs[11] = FVector2D(CubeSize.X, 0.0f);
	// X+
	UVs[12] = FVector2D(0.0f, 0.0f);
	UVs[13] = FVector2D(0.0f, CubeSize.Z);
	UVs[14] = FVector2D(CubeSize.Y, CubeSize.Z);
	UVs[15] = FVector2D(CubeSize.Y, 0.0f);
	// Y-
	UVs[16] = FVector2D(0.0f, 0.0f);
	UVs[17] = FVector2D(0.0f, CubeSize.Z);
	UVs[18] = FVector2D(CubeSize.X, CubeSize.Z);
	UVs[19] = FVector2D(CubeSize.X, 0.0f);
	// Z-
	UVs[20] = FVector2D(0.0f, 0.0f);
	UVs[21] = FVector2D(0.0f, CubeSize.X);
	UVs[22] = FVector2D(CubeSize.Y, CubeSize.X);
	UVs[23] = FVector2D(CubeSize.Y, 0.0f);

	// Create mesh
	MeshComponent->ClearAllMeshSections();
	MeshComponent->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, TArray<FLinearColor>(), Tangents, false);

	BoxComponent->SetBoxExtent(FVector(CubeSize) * 200.0f);
}
