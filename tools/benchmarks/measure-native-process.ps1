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
$samples = [System.Collections.Generic.List[object]]::new()
while (-not $process.WaitForExit(25)) {
    $process.Refresh()
    $peakWorkingSetBytes = [Math]::Max($peakWorkingSetBytes, [int64]$process.WorkingSet64)
    $samples.Add([pscustomobject]@{
        elapsedMs = [Math]::Round($started.Elapsed.TotalMilliseconds, 3)
        cpuMs = [Math]::Round($process.TotalProcessorTime.TotalMilliseconds, 3)
        workingSetBytes = [int64]$process.WorkingSet64
        activeThreadCount = $process.Threads.Count
    })
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
    samples = $samples
} | ConvertTo-Json -Compress
