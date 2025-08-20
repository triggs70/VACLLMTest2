You are my Unreal project automation copilot. We are at the Unreal project root (same folder as the .uproject).

OPERATING RULES
1) Plan first. Then wait for me to reply **APPROVE** before running anything.
2) Use Windows PowerShell commands only. Quote paths with spaces; no placeholders.
3) **Record only on success**: Do NOT write to docs/ or commit/push unless the copy + summary complete successfully.

WHAT I WANT TO DO IN THIS STEP
- Copy my NHL shots CSV from the Windows Desktop into a tracked repo folder: `.Datashots.csv`
- Create a brief Markdown summary of the CSV (column headers + total row count) in `docsdatashots-summary.md`
- Update the repository ONLY if successful:
  - Append to `docsLOG.md`
  - Create a concise `docschanges<timestamp>-data-import.md`
  - Save THIS prompt text into `docsprompts03_add-data.md`
  - `git add/commit/push`
- If anything fails, abort with a readable error and **do not** write to docs or push.

CSV SOURCE LOCATION
- Search for CSVs on my Desktop folder: `$HOMEDesktop*.csv`
- If more than one CSV is found, print the list and ask me to choose the exact file (then wait for my reply). Otherwise, use the single match.
- Target path: `.Datashots.csv` (overwrite if it already exists, but make a backup as `.Datashots.csv.bak` first if present).

DOCS & GIT CONVENTIONS
- Use timestamp `$ts = Get-Date -Format 'yyyy-MM-dd_HH-mm-ss'`
- Create folders if missing: `.docsprompts`, `.docschanges`, `.docsdata`, `.Data`
- For the CSV summary:
  - Headers: list the column names in order
  - Row count: count data rows (exclude header)
  - Save to `docsdatashots-summary.md`
- For `docsLOG.md`: append a section containing:
  - `$ts`, step title ("Import CSV from Desktop"), current branch, and latest commit hash (short)
  - The **exact** commands executed (fenced code block)
- For `docschanges$ts-data-import.md`: summarize what changed (created/overwritten files, row count, etc.)
- Save THIS prompt verbatim to `docsprompts03_add-data.md` **only if the step is successful**.
- After committing, push to the current branch’s upstream (`git push`). If no upstream is set, set it (`git push -u origin <branch>`)

PRINT FIRST, DO NOT EXECUTE YET
1) Show a numbered plan of the actions.
2) Show the exact PowerShell command block you will run using a try/catch pattern like this:
   - Define `$ts`, detect `$branch`, `$repoRoot`, `$projName` (from the .uproject filename)
   - Detect CSV source:
     * If multiple matches on `$HOMEDesktop*.csv`, print them and STOP to ask me which one to use (by full path). Do not proceed until I reply with the path. Do not proceed until I reply with the path.
     * Else set `$CsvSource` to the single match.
   - `New-Item -ItemType Directory -Force` for `.Data` and docs subfolders
   - If `.Datashots.csv` exists, copy to `shots.csv.bak` with timestamp suffix
   - Copy `$CsvSource` → `.Datashots.csv`
   - Validate: file exists and length > 0
   - Build summary:
     * `$csvLines = Get-Content -Raw ".Datashots.csv" -Encoding UTF8`
     * `$headers = ($csvLines -split "`r?`n")[0] -split ","
     * `$rowCount = ( ($csvLines -split "`r?`n").Where({$_ -ne ""}).Count ) - 1
     * Write `docsdatashots-summary.md` with project name, file path, row count, and headers (as a markdown list)
   - If everything succeeded → only then:
     * Append a section to `docsLOG.md` with `$ts`, branch, commit hash (short), and the exact commands executed
     * Write `docschanges$ts-data-import.md` describing the changes
     * Save THIS prompt text to `docsprompts03_add-data.md`
     * `git add .`
     * `git commit -m "data: import shots.csv and add summary ($ts)"`
     * Push: if upstream set → `git push`; else set upstream for current branch and push
   - In `catch`, print a clear error and exit **without** writing to docs or committing/pushing.

3) Then stop and wait for **APPROVE**.