param(
  [string]$Root = (Split-Path -Parent $PSScriptRoot)
)
$ErrorActionPreference = 'Stop'
$linksPath = Join-Path $Root 'skill_effect_source_links.json'
$outDir = Join-Path $Root 'docs\sources\skills'
New-Item -ItemType Directory -Force -Path $outDir | Out-Null
$links = (Get-Content -LiteralPath $linksPath -Raw | ConvertFrom-Json).sources
$manifest = @()
foreach ($source in $links) {
  $url = [uri]$source.url
  $query = [System.Web.HttpUtility]::ParseQueryString($url.Query)
  $query.Remove('s_type'); $query.Remove('s_keyword')
  $cleanUrl = $url.GetLeftPart([System.UriPartial]::Path)
  if ($query.Count) { $cleanUrl += '?' + $query.ToString() }
  $tempHtml = Join-Path $env:TEMP ('toram-skill-source-' + $source.tree_id + '.html')
  & curl.exe -L --compressed -A 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 Chrome/131.0.0.0 Safari/537.36' -sS $cleanUrl -o $tempHtml
  if ($LASTEXITCODE -ne 0) { throw "원문 요청 실패: $($source.tree_id)" }
  $html = Get-Content -LiteralPath $tempHtml -Raw -Encoding utf8
  $match = [regex]::Match($html, '"articleBody"\s*:\s*"((?:\\.|[^"\\])*)"', [System.Text.RegularExpressions.RegexOptions]::Singleline)
  if (-not $match.Success) { throw "articleBody를 찾지 못했습니다: $($source.tree_id)" }
  $body = ConvertFrom-Json ('"' + $match.Groups[1].Value + '"')
  $body = $body -replace "`r`n", "`n"
  $output = Join-Path $outDir ($source.tree_id + '.txt')
  Set-Content -LiteralPath $output -Value $body -Encoding utf8
  $hash = (Get-FileHash -Algorithm SHA256 -LiteralPath $output).Hash.ToLowerInvariant()
  $manifest += [pscustomobject]@{ tree_id=$source.tree_id; source_url=$cleanUrl; cached_at=(Get-Date).ToUniversalTime().ToString('o'); file=('docs/sources/skills/' + $source.tree_id + '.txt'); sha256=$hash; characters=$body.Length }
}
$manifest | ConvertTo-Json -Depth 4 | Set-Content -LiteralPath (Join-Path $outDir 'manifest.json') -Encoding utf8
