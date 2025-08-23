## Summary of Changes

- Updated `Source/NHLShotTracking/HeatMapGenerator.cpp` to fix a build error related to `UTexture2D::PlatformData` access.

### Before
- The code directly accessed `HeatMapTexture->PlatformData`, which is no longer allowed in UE 5.6.

### After
- The code now uses `HeatMapTexture->GetPlatformData()` to access the mip data.
- The pixel data is now correctly copied using an `FColor` array and `FMemory::Memcpy`.