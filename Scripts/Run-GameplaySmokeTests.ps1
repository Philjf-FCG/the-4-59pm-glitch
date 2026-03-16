param(
    [string]$EngineRoot,
    [string]$EditorCmd,
    [string]$TestFilter = "Project.Glitch459PM"
)

$runnerPath = Join-Path $PSScriptRoot "Run-UnrealAutomation.ps1"
& $runnerPath -EngineRoot $EngineRoot -EditorCmd $EditorCmd -TestFilter $TestFilter
if ($LASTEXITCODE -ne 0) {
    throw "Gameplay smoke test run failed with exit code $LASTEXITCODE."
}