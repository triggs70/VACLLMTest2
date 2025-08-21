#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ShotData.h"
#include "ShotDataLoader.generated.h"

UCLASS()
class NHLSHOTTRACKING_API UShotDataLoader : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Shot Data")
    static bool LoadCSVShots(const FString& CSVPath, TArray<FShotRow>& OutShotRows, FString& OutError);

    UFUNCTION(BlueprintCallable, Category = "Shot Data")
    static void NormalizeShotstoUV(const TArray<FShotRow>& ShotRows, TArray<FVector2D>& OutUVCoords);
};
