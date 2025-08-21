## 2025-08-20_15-35-00 - Connect remote & initial push
- **Branch:** main
- **Commit:** edee4ae

```powershell
git remote add origin https://github.com/triggs70/VACLLMTest2.git
git push -u origin master:main
git branch -M main
```

## 2025-08-20_15-40-00 - Import CSV from Desktop
- **Branch:** main
- **Commit:** a66665c

```powershell
copy nhl-shots-sample.csv Data\shots.csv
# Summary generation commands were also run
```

## 2025-08-21_17-25-00 - Add FShotRow USTRUCT
- **Branch:** main
- **Commit:** 7979130

```powershell
# wrote file Source/NHLShotTracking/ShotData.h
# wrote file Source/NHLShotTracking/ShotData.cpp
git add .
git commit -m "feat: Add FShotRow USTRUCT for CSV data"
```
