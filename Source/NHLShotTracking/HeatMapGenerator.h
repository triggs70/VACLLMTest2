#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HeatMapGenerator.generated.h"

UCLASS()
class NHLSHOTTRACKING_API UHeatMapGenerator : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "HeatMap")
    static UTexture2D* GenerateHeatMap(const TArray<FVector2D>& UVPoints, bool bUseLogScale);
};