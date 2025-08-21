#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ShotData.generated.h"

USTRUCT(BlueprintType)
struct FShotRow : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float X;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Y;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsGoal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Period;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Team;
};
