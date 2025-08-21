# Gemini Project Rules

This set of rules applies to every prompt run for this unreal project

## Rules
1. Plan first - show the step by step process plan and exact powershell commands, wait for me to reply **Approve** before running anything.
2. Commands must be valid in powershell, quote paths with spaces.
3. Assume all prompts are executed from the unreal project root
4. Updating Docs - On a successfully run prompt, update:
    - `docs/LOG.md` with a timestamp, branch, commit hash and commands used
    - `docs/changes/<timestamp>-<step>.md` with the summary of before/after changes
    - `docs/prompts/<step>.md` saving the exact prompt text
5. Git - only commit/push on a successfully run prompt. If a prompt fails, do not log or commit any changes.

## Style
- Be explicit, use full paths and file names.
- Keep explanations/summaries short.
- If multiple file matches exist, ask me to confirm which is the correct file before continuing. 