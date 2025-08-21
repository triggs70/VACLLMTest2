#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HeatMapDisplayActor.generated.h"

UCLASS()
class NHLSHOTTRACKING_API AHeatMapDisplayActor : public AActor
{
    GENERATED_BODY()

public:
    AHeatMapDisplayActor();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, Category = "HeatMap")
    FString CsvPathRel = "Data/shots.csv";

    UPROPERTY(EditAnywhere, Category = "HeatMap")
    UMaterialInterface* BaseMaterial;

    UPROPERTY(VisibleAnywhere, Category = "HeatMap")
    UStaticMeshComponent* PlaneMesh;
};