$ErrorActionPreference = 'Stop'
$exe = Join-Path $PSScriptRoot 'merge_sorted.exe'
$cases = @(
    @{ Name='sample'; Input="3`n22 21 19`n4`n92 91 31 2"; Expected='2,19,21,22,31,91,92' },
    @{ Name='both empty'; Input="0`n0"; Expected='' },
    @{ Name='A empty'; Input="0`n3`n5 2 -1"; Expected='-1,2,5' },
    @{ Name='B empty'; Input="3`n5 2 -1`n0"; Expected='-1,2,5' },
    @{ Name='duplicates'; Input="3`n5 3 3`n3`n4 3 1"; Expected='1,3,3,3,4,5' },
    @{ Name='A before B'; Input="2`n2 1`n2`n4 3"; Expected='1,2,3,4' },
    @{ Name='negative and singleton'; Input="1`n-5`n1`n-9"; Expected='-9,-5' }
)
foreach ($case in $cases) {
    $actual = @( $case.Input | & $exe )
    if ($LASTEXITCODE -ne 0 -or $actual.Count -ne 2 -or
        $actual[0] -cne 'The current List is:' -or $actual[1] -cne $case.Expected) {
        throw "Failed: $($case.Name); actual: $($actual -join '|')"
    }
}
foreach ($bad in @("-1", "1`nx", "1`n5`n2`n7", "")) {
    $null = $bad | & $exe
    if ($LASTEXITCODE -eq 0) { throw 'Invalid input unexpectedly accepted' }
}
$reviewDir = Split-Path $PSScriptRoot -Parent
$source = Get-Content -Raw -LiteralPath (Join-Path $reviewDir '单链表_有序合并_题解.c')
$doc = Get-Content -Raw -LiteralPath (Join-Path $reviewDir '单链表_有序合并_题解.md')
$block = [regex]::Match(($doc -split '## 完整 C 语言代码', 2)[1], '(?s)```c\r?\n(.*?)\r?\n```').Groups[1].Value
if ($block.Replace("`r`n", "`n").TrimEnd() -cne $source.Replace("`r`n", "`n").TrimEnd()) {
    throw 'Markdown code differs from C source'
}
Write-Output 'PASS: 7 merge cases, 4 invalid-input cases, Markdown/source consistency.'

