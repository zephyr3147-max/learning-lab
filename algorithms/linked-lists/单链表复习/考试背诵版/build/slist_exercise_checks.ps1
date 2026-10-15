param(
    [string]$Program = (Join-Path $PSScriptRoot 'slist_exercise.exe')
)
$ErrorActionPreference = 'Stop'
if (-not (Test-Path -LiteralPath $Program))
{
    throw 'Compile the exercise into build/slist_exercise.exe first.'
}
$cases = @(
    @{ Name='sample'; Input=@('5','1 2 3 4 5','3 6','4'); Output='1 2 6 3 5' },
    @{ Name='invalid-low'; Input=@('3','1 2 3','0 9','2'); Output='1 3' },
    @{ Name='invalid-high'; Input=@('3','1 2 3','5 9','2'); Output='1 3' },
    @{ Name='front-insert'; Input=@('3','1 2 3','1 9','3'); Output='9 1 2' },
    @{ Name='tail-insert'; Input=@('3','1 2 3','4 9','1'); Output='2 3 9' },
    @{ Name='empty-insert-delete'; Input=@('0','1 9','9'); Output='' },
    @{ Name='not-found'; Input=@('2','1 2','3 3','99'); Output='1 2 3' },
    @{ Name='first-match-only'; Input=@('3','2 2 3','0 9','2'); Output='2 3' },
    @{ Name='delete-last-element'; Input=@('1','7','3 9','7'); Output='' }
)
foreach ($caseData in $cases)
{
    $actual = @(($caseData.Input -join [Environment]::NewLine) | & $Program)
    if ($LASTEXITCODE -ne 0)
    {
        throw "Nonzero exit code: $($caseData.Name)"
    }
    if (($actual -join [Environment]::NewLine) -cne $caseData.Output)
    {
        throw "Output mismatch: $($caseData.Name)"
    }
    Write-Output "PASS: $($caseData.Name)"
}
Write-Output "$($cases.Count) linked-list exercise checks passed."

