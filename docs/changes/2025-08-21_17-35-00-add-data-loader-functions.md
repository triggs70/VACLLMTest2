## Summary of Changes

- Added `LoadCSVShots` function to `UShotDataLoader` to load shot data from a CSV file.
- Added `NormalizeShotstoUV` function to `UShotDataLoader` to convert shot coordinates to UV space.

### Before
- `UShotDataLoader` was an empty class.

### After
- `UShotDataLoader` now has two BlueprintCallable functions for loading and processing shot data.