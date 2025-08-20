You are my Unreal project automation copilot. We are still at the Unreal project root.

OPERATING RULES
1) Plan first, then wait for me to say **APPROVE** before you run any commands.
2) Use Windows PowerShell only. Quote paths with spaces. No placeholders.
3) After each action block, print a brief “What changed” summary.

GOAL FOR THIS STEP
- Connect this local Git repo to my GitHub remote and push the current branch.
- Record THIS prompt, the commands executed, and a concise change summary in docs/.

REMOTE INFO
- Remote URL: https://github.com/triggs70/VACLLMTest2.git

RECORD-KEEPING
- Before running anything, save this prompt verbatim to: `docs/prompts/02_connect-remote.md`
- Use `$ts = Get-Date -Format 'yyyy-MM-dd_HH-mm-ss'` for filenames/entries.
- After the command block runs:
  - Append to `docs/LOG.md` a new section with:
    - `$ts`, step title (“Connect remote & initial push”)
    - current branch name
    - latest commit hash (short)
    - the exact commands executed (fenced code block)
  - Create `docs/changes/$ts-remote.md` summarizing:
    - remote URL
    - branch pushed & upstream
    - output of `git remote -v`

SAFETY / EDGE CASES
- Detect if a remote named `origin` exists:
  - If not, `git remote add origin <URL>`
  - If yes, `git remote set-url origin <URL>`
- Detect current branch; if detached/empty, create/switch to `main`:
  - If branch is `master`, rename to `main` (`git branch -M main`) for consistency.
- If `user.name` / `user.email` aren’t set, set them to placeholders:
  - `git config user.name "Your Name"`
  - `git config user.email "you@example.com"`
- If authentication is required, the `git push` will prompt me; that’s fine.

DELIVERABLES FOR THIS STEP
A) `docs/prompts/02_connect-remote.md` containing this exact prompt.
B) Remote `origin` set to the URL above.
C) Current branch pushed to GitHub with upstream tracking set.
D) `docs/LOG.md` updated with a full command transcript for this step.
E) `docs/changes/$ts-remote.md` created with a concise summary and `git remote -v` output.

PRINT FIRST, DO NOT EXECUTE YET
1) Show the numbered plan.
2) Show the exact PowerShell commands you will run. They should:
   - set `$ts`
   - write `docs/prompts/02_connect-remote.md` with the verbatim prompt text
   - ensure `docs/changes` exists
   - detect/set `$branch`
   - ensure `user.name`/`user.email` are set (only if missing)
   - add or set-url for `origin`
   - show `git remote -v`
   - push current branch and set upstream (`git push -u origin $branch`)
   - append a section to `docs/LOG.md` with `$ts`, branch, commit hash, and the commands block
   - write `docs/changes/$ts-remote.md` summarizing the change, including `git remote -v` output
3) Then stop and wait for **APPROVE**.