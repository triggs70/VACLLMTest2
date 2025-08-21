## Summary of Changes

- Created `Source/NHLShotTracking/HeatMapDisplayActor.h` with the definition of the `AHeatMapDisplayActor` AActor.
- Created `Source/NHLShotTracking/HeatMapDisplayActor.cpp` with the implementation of the actor's logic.

### Before
- No actor existed for displaying the heatmap.

### After
- `AHeatMapDisplayActor` class is now available for use in the editor. On BeginPlay, it loads the CSV data, generates a heatmap, and applies it to a plane mesh.