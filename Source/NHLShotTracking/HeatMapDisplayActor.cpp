#include "HeatMapDisplayActor.h"
#include "ShotDataLoader.h"
#include "HeatMapGenerator.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"
#include "Misc/Paths.h"

AHeatMapDisplayActor::AHeatMapDisplayActor()
{
    PrimaryActorTick.bCanEverTick = false;

    PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMesh"));
    RootComponent = PlaneMesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneAsset(TEXT("/Engine/BasicShapes/Plane"));
    if (PlaneAsset.Succeeded())
    {
        PlaneMesh->SetStaticMesh(PlaneAsset.Object);
    }
}

void AHeatMapDisplayActor::BeginPlay()
{
    Super::BeginPlay();

    if (!BaseMaterial)
    {
        UE_LOG(LogTemp, Warning, TEXT("BaseMaterial is not set in AHeatMapDisplayActor."));
        return;
    }

    FString FullCSVPath = FPaths::Combine(FPaths::ProjectDir(), CsvPathRel);

    TArray<FShotRow> ShotRows;
    FString Error;
    if (UShotDataLoader::LoadCSVShots(FullCSVPath, ShotRows, Error))
    {
        TArray<FVector2D> UVCoords;
        UShotDataLoader::NormalizeShotstoUV(ShotRows, UVCoords);

        UTexture2D* HeatMapTexture = UHeatMapGenerator::GenerateHeatMap(UVCoords, true);

        if (HeatMapTexture)
        {
            UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);
            if (DynMaterial)
            {
                DynMaterial->SetTextureParameterValue(FName("HeatTex"), HeatMapTexture);
                PlaneMesh->SetMaterial(0, DynMaterial);
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load CSV: %s"), *Error);
    }
}