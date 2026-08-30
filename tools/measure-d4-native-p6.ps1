param(
    [Parameter(Mandatory = $true)][string]$Binary,
    [Parameter(Mandatory = $true)][string]$InputPath,
    [Parameter(Mandatory = $true)][string]$Output,
    [Parameter(Mandatory = $true)][string]$ErrorOutput
)

$ErrorActionPreference = 'Stop'
$started = [System.Diagnostics.Stopwatch]::StartNew()
$process = Start-Process -FilePath $Binary -RedirectStandardInput $InputPath -RedirectStandardOutput $Output -RedirectStandardError $ErrorOutput -PassThru -WindowStyle Hidden
$peakWorkingSetBytes = 0
while (-not $process.WaitForExit(25)) {
    $process.Refresh()
    $peakWorkingSetBytes = [Math]::Max($peakWorkingSetBytes, [int64]$process.WorkingSet64)
}
$process.WaitForExit()
$process.Refresh()
$peakWorkingSetBytes = [Math]::Max($peakWorkingSetBytes, [int64]$process.PeakWorkingSet64)
$started.Stop()
[pscustomobject]@{
    exitCode = $process.ExitCode
    wallMs = [Math]::Round($started.Elapsed.TotalMilliseconds, 3)
    cpuMs = [Math]::Round($process.TotalProcessorTime.TotalMilliseconds, 3)
    peakWorkingSetBytes = $peakWorkingSetBytes
} | ConvertTo-Json -Compress
