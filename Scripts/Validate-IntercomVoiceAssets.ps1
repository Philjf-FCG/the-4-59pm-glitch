param(
    [string]$ManifestPath = (Join-Path $PSScriptRoot "intercom_tts_manifest.json"),
    [string]$AssetDirectory = (Join-Path $PSScriptRoot "..\Content\Audio\VO\Intercom")
)

$resolvedManifest = (Resolve-Path $ManifestPath).Path
$manifest = Get-Content $resolvedManifest -Raw | ConvertFrom-Json

if (-not (Test-Path $AssetDirectory)) {
    Write-Output "Missing asset directory: $AssetDirectory"
    exit 1
}

$missing = @()
$present = @()

foreach ($line in $manifest.lines) {
    $expectedAsset = Join-Path $AssetDirectory ($line.key + ".uasset")
    if (Test-Path $expectedAsset) {
        $present += $line.key
    }
    else {
        $missing += $line.key
    }
}

Write-Output ("Present voice assets: {0}" -f $present.Count)
foreach ($key in $present) {
    Write-Output ("  OK  " + $key)
}

Write-Output ("Missing voice assets: {0}" -f $missing.Count)
foreach ($key in $missing) {
    Write-Output ("  MISS " + $key)
}

if ($missing.Count -gt 0) {
    exit 2
}