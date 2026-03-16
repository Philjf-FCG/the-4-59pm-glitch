param(
    [string]$TestFilter = "Project.Glitch459PM",
    [string]$EngineRoot,
    [string]$EditorCmd,
    [string]$ProjectPath = (Join-Path $PSScriptRoot "..\The459PMGlitch.uproject"),
    [switch]$ListOnly
)

$resolvedProjectPath = (Resolve-Path $ProjectPath).Path

if (-not $EditorCmd -and $EngineRoot) {
    $EditorCmd = Join-Path $EngineRoot "Engine\Binaries\Win64\UnrealEditor-Cmd.exe"
}

if (-not $EditorCmd) {
    $defaultEditorCmd = "C:\Program Files\Epic Games\UE_5.6\Engine\Binaries\Win64\UnrealEditor-Cmd.exe"
    if (Test-Path $defaultEditorCmd) {
        $EditorCmd = $defaultEditorCmd
    }
}

if (-not $EditorCmd -or -not (Test-Path $EditorCmd)) {
    throw "Unable to locate UnrealEditor-Cmd.exe. Pass -EngineRoot or -EditorCmd."
}

$savedDir = Join-Path (Split-Path $resolvedProjectPath -Parent) "Saved"
$reportDir = Join-Path $savedDir "AutomationReports"
$logDir = Join-Path $savedDir "Logs"
$logPath = Join-Path $logDir "Automation-Run.log"

New-Item -ItemType Directory -Force -Path $reportDir | Out-Null
New-Item -ItemType Directory -Force -Path $logDir | Out-Null

$execCmds = if ($ListOnly) {
    "Automation List; Quit"
} else {
    "Automation RunTests $TestFilter; Quit"
}

$arguments = @(
    $resolvedProjectPath,
    "-unattended",
    "-nop4",
    "-nosplash",
    "-NullRHI",
    "-stdout",
    "-FullStdOutLogOutput",
    "-TestExit=Automation Test Queue Empty",
    "-ReportExportPath=$reportDir",
    "-log=$logPath",
    "-ExecCmds=$execCmds"
)

& $EditorCmd @arguments
if ($LASTEXITCODE -ne 0) {
    throw "Unreal automation run failed with exit code $LASTEXITCODE."
}