## Summary of Changes

- Created `Source/NHLShotTracking/HeatMapGenerator.h` with the definition of the `UHeatMapGenerator` UCLASS.
- Created `Source/NHLShotTracking/HeatMapGenerator.cpp` with the implementation of the `GenerateHeatMap` function.

### Before
- No class existed for generating heatmaps.

### After
- `UHeatMapGenerator` class is now available for use in Blueprints and C++ to generate a heatmap texture from a list of UV points.