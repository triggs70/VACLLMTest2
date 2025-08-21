#include "ShotDataLoader.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

bool UShotDataLoader::LoadCSVShots(const FString& CSVPath, TArray<FShotRow>& OutShotRows, FString& OutError)
{
    if (!FPaths::FileExists(CSVPath))
    {
        OutError = FString::Printf(TEXT("File not found at path: %s"), *CSVPath);
        return false;
    }

    TArray<FString> Lines;
    if (!FFileHelper::LoadFileToStringArray(Lines, *CSVPath))
    {
        OutError = FString::Printf(TEXT("Failed to load file: %s"), *CSVPath);
        return false;
    }

    // Skip header
    for (int32 i = 1; i < Lines.Num(); ++i)
    {
        TArray<FString> Columns;
        Lines[i].ParseIntoArray(Columns, TEXT(","), true);

        if (Columns.Num() >= 5)
        {
            FShotRow ShotRow;
            ShotRow.X = FCString::Atof(*Columns[0]);
            ShotRow.Y = FCString::Atof(*Columns[1]);
            ShotRow.bIsGoal = Columns[2].ToBool();
            ShotRow.Period = FCString::Atoi(*Columns[3]);
            ShotRow.Team = Columns[4];
            OutShotRows.Add(ShotRow);
        }
    }

    return true;
}

void UShotDataLoader::NormalizeShotstoUV(const TArray<FShotRow>& ShotRows, TArray<FVector2D>& OutUVCoords)
{
    const float RinkWidth = 60.0f;
    const float RinkHeight = 25.0f;

    for (const FShotRow& ShotRow : ShotRows)
    {
        FVector2D UVCoord;
        UVCoord.X = (ShotRow.X + (RinkWidth / 2.0f)) / RinkWidth;
        UVCoord.Y = (ShotRow.Y + (RinkHeight / 2.0f)) / RinkHeight;
        OutUVCoords.Add(UVCoord);
    }
}
