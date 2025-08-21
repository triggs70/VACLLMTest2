#include "HeatMapGenerator.h"
#include "Engine/Texture2D.h"

UTexture2D* UHeatMapGenerator::GenerateHeatMap(const TArray<FVector2D>& UVPoints, bool bUseLogScale)
{
    const int32 Width = 512;
    const int32 Height = 256;
    TArray<float> HeatGrid;
    HeatGrid.Init(0.0f, Width * Height);

    // Binning
    for (const FVector2D& UVPoint : UVPoints)
    {
        int32 X = FMath::Clamp(FMath::FloorToInt(UVPoint.X * Width), 0, Width - 1);
        int32 Y = FMath::Clamp(FMath::FloorToInt(UVPoint.Y * Height), 0, Height - 1);
        HeatGrid[Y * Width + X]++;
    }

    // Blur (Simple Box Blur)
    TArray<float> BlurredGrid = HeatGrid;
    int32 BlurKernelSize = 5;
    for (int32 y = 0; y < Height; ++y)
    {
        for (int32 x = 0; x < Width; ++x)
        {
            float Sum = 0.0f;
            int32 Count = 0;
            for (int32 ky = -BlurKernelSize; ky <= BlurKernelSize; ++ky)
            {
                for (int32 kx = -BlurKernelSize; kx <= BlurKernelSize; ++kx)
                {
                    int32 nx = x + kx;
                    int32 ny = y + ky;
                    if (nx >= 0 && nx < Width && ny >= 0 && ny < Height)
                    {
                        Sum += HeatGrid[ny * Width + nx];
                        Count++;
                    }
                }
            }
            BlurredGrid[y * Width + x] = Sum / Count;
        }
    }
    HeatGrid = BlurredGrid;

    // Normalization
    float MaxValue = 0.0f;
    if (bUseLogScale)
    {
        for (float& Value : HeatGrid)
        {
            Value = FMath::Loge(1.0f + Value);
        }
    }

    for (const float& Value : HeatGrid)
    {
        if (Value > MaxValue)
        {
            MaxValue = Value;
        }
    }

    if (MaxValue > 0.0f)
    {
        for (float& Value : HeatGrid)
        {
            Value /= MaxValue;
        }
    }

    // Texture Creation
    UTexture2D* HeatMapTexture = UTexture2D::CreateTransient(Width, Height, PF_B8G8R8A8);
    if (HeatMapTexture)
    {
        FTexture2DMipMap& Mip = HeatMapTexture->PlatformData->Mips[0];
        void* Data = Mip.BulkData.Lock(LOCK_READ_WRITE);
        uint8* PixelData = static_cast<uint8*>(Data);

        for (int32 i = 0; i < HeatGrid.Num(); ++i)
        {
            uint8 PixelValue = static_cast<uint8>(HeatGrid[i] * 255.0f);
            PixelData[i * 4 + 0] = PixelValue; // Blue
            PixelData[i * 4 + 1] = PixelValue; // Green
            PixelData[i * 4 + 2] = PixelValue; // Red
            PixelData[i * 4 + 3] = 255;      // Alpha
        }

        Mip.BulkData.Unlock();
        HeatMapTexture->UpdateResource();
    }

    return HeatMapTexture;
}