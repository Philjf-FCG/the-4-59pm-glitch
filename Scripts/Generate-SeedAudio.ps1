param(
    [string]$OutputRoot = (Join-Path $PSScriptRoot "..\ExternalAssets\GeneratedAudio"),
    [int]$SampleRate = 48000
)

$pythonCandidates = @("py", "python")
$pythonCommand = $null

foreach ($candidate in $pythonCandidates) {
    $command = Get-Command $candidate -ErrorAction SilentlyContinue | Select-Object -First 1
    if ($command) {
        $pythonCommand = $candidate
        break
    }
}

if (-not $pythonCommand) {
    throw "Unable to locate a Python interpreter. Install Python or add py.exe/python.exe to PATH."
}

$generatorPath = Join-Path $PSScriptRoot "Generate-SeedAudio.py"
$manifestPath = Join-Path $PSScriptRoot "intercom_tts_manifest.json"

& $pythonCommand $generatorPath --output-root $OutputRoot --manifest $manifestPath --sample-rate $SampleRate
if ($LASTEXITCODE -ne 0) {
    throw "Seed audio generation failed with exit code $LASTEXITCODE."
}