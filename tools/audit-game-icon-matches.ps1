param(
  [string]$SkillRoot = (Join-Path $PSScriptRoot '..\assets\icons\skills'),
  [string]$GameIconRoot = (Join-Path $PSScriptRoot '..\assets\game-data\ui\game-icons'),
  [string]$OutputPath = (Join-Path $PSScriptRoot '..\assets\source-data\game-icon-skill-match-candidates.json'),
  [ValidateRange(1, 10)][int]$Top = 3,
  [switch]$Force
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'
if ((Test-Path -LiteralPath $OutputPath) -and -not $Force) { throw "Output already exists: $OutputPath. Use -Force only when intentionally regenerating it." }

$runtimeDir = 'C:\Users\조연우\.cache\codex-runtimes\codex-primary-runtime\dependencies\native\powershell'
$assemblies = @(
  (Join-Path $runtimeDir 'System.Drawing.Common.dll'),
  (Join-Path $runtimeDir 'System.Private.Windows.GdiPlus.dll'),
  (Join-Path $runtimeDir 'System.Private.Windows.Core.dll'),
  (Join-Path $runtimeDir 'System.Drawing.Primitives.dll')
)

$typeDefinition = @"
using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;

public sealed class IconCandidate {
  public string SkillIconPath { get; set; }
  public double Distance { get; set; }
}

public sealed class IconMatch {
  public string GameIconPath { get; set; }
  public IconCandidate[] Candidates { get; set; }
}

internal sealed class IconDescriptor {
  public string Path;
  public byte[] Features;
}

public static class IconMatcher {
  private const int CanvasSize = 16;
  private const int ContentSize = 14;

  private static Rectangle GetContentBounds(Bitmap source) {
    using (var normalized = new Bitmap(source.Width, source.Height, PixelFormat.Format32bppArgb)) {
      using (var graphics = Graphics.FromImage(normalized)) graphics.DrawImageUnscaled(source, 0, 0);
      var data = normalized.LockBits(new Rectangle(0, 0, normalized.Width, normalized.Height), ImageLockMode.ReadOnly, PixelFormat.Format32bppArgb);
      try {
        var raw = new byte[Math.Abs(data.Stride) * normalized.Height];
        Marshal.Copy(data.Scan0, raw, 0, raw.Length);
        var left = normalized.Width; var top = normalized.Height; var right = -1; var bottom = -1;
        for (var y = 0; y < normalized.Height; y++) for (var x = 0; x < normalized.Width; x++) {
          if (raw[y * data.Stride + x * 4 + 3] != 0) {
            if (x < left) left = x; if (x > right) right = x;
            if (y < top) top = y; if (y > bottom) bottom = y;
          }
        }
        return right < 0 ? new Rectangle(0, 0, source.Width, source.Height) : Rectangle.FromLTRB(left, top, right + 1, bottom + 1);
      } finally { normalized.UnlockBits(data); }
    }
  }

  private static IconDescriptor Describe(string path) {
    using (var source = new Bitmap(path)) {
      var bounds = GetContentBounds(source);
      using (var canvas = new Bitmap(CanvasSize, CanvasSize, PixelFormat.Format32bppArgb)) {
        using (var graphics = Graphics.FromImage(canvas)) {
          graphics.Clear(Color.Transparent);
          graphics.InterpolationMode = InterpolationMode.HighQualityBicubic;
          graphics.PixelOffsetMode = PixelOffsetMode.HighQuality;
          graphics.CompositingQuality = CompositingQuality.HighQuality;
          var scale = Math.Min((double)ContentSize / bounds.Width, (double)ContentSize / bounds.Height);
          var width = bounds.Width * scale; var height = bounds.Height * scale;
          var destination = new RectangleF((float)((CanvasSize - width) / 2.0), (float)((CanvasSize - height) / 2.0), (float)width, (float)height);
          graphics.DrawImage(source, destination, bounds, GraphicsUnit.Pixel);
        }
        var data = canvas.LockBits(new Rectangle(0, 0, CanvasSize, CanvasSize), ImageLockMode.ReadOnly, PixelFormat.Format32bppArgb);
        try {
          var raw = new byte[Math.Abs(data.Stride) * CanvasSize];
          Marshal.Copy(data.Scan0, raw, 0, raw.Length);
          var features = new byte[CanvasSize * CanvasSize * 4];
          var index = 0;
          for (var y = 0; y < CanvasSize; y++) for (var x = 0; x < CanvasSize; x++) {
            var offset = y * data.Stride + x * 4;
            var alpha = raw[offset + 3];
            features[index++] = (byte)(raw[offset + 2] * alpha / 255);
            features[index++] = (byte)(raw[offset + 1] * alpha / 255);
            features[index++] = (byte)(raw[offset] * alpha / 255);
            features[index++] = alpha;
          }
          return new IconDescriptor { Path = path, Features = features };
        } finally { canvas.UnlockBits(data); }
      }
    }
  }

  private static double Distance(IconDescriptor left, IconDescriptor right) {
    long sum = 0;
    for (var i = 0; i < left.Features.Length; i++) { var diff = left.Features[i] - right.Features[i]; sum += diff * diff; }
    return Math.Sqrt(sum / (double)(left.Features.Length * 255 * 255));
  }

  public static IconMatch[] Find(string[] skillPaths, string[] gamePaths, int top) {
    var skills = new IconDescriptor[skillPaths.Length];
    for (var i = 0; i < skillPaths.Length; i++) skills[i] = Describe(skillPaths[i]);
    var matches = new IconMatch[gamePaths.Length];
    for (var gameIndex = 0; gameIndex < gamePaths.Length; gameIndex++) {
      var game = Describe(gamePaths[gameIndex]);
      var best = new IconCandidate[top];
      for (var skillIndex = 0; skillIndex < skills.Length; skillIndex++) {
        var candidate = new IconCandidate { SkillIconPath = skills[skillIndex].Path, Distance = Distance(game, skills[skillIndex]) };
        for (var slot = 0; slot < top; slot++) {
          if (best[slot] == null || candidate.Distance < best[slot].Distance) {
            for (var shift = top - 1; shift > slot; shift--) best[shift] = best[shift - 1];
            best[slot] = candidate;
            break;
          }
        }
      }
      matches[gameIndex] = new IconMatch { GameIconPath = game.Path, Candidates = best };
    }
    return matches;
  }
}
"@
Add-Type -TypeDefinition $typeDefinition -ReferencedAssemblies $assemblies

$skillFiles = @(Get-ChildItem -LiteralPath $SkillRoot -Recurse -File -Filter '*.png' | Sort-Object FullName | Select-Object -ExpandProperty FullName)
$gameFiles = @(Get-ChildItem -LiteralPath $GameIconRoot -File -Filter '*.png' | Sort-Object FullName | Select-Object -ExpandProperty FullName)
if ($skillFiles.Count -eq 0 -or $gameFiles.Count -eq 0) { throw 'No PNG files were found in one or both input directories.' }
$root = (Resolve-Path -LiteralPath (Join-Path $PSScriptRoot '..')).Path
$matches = [IconMatcher]::Find($skillFiles, $gameFiles, $Top)
$relative = { param([string]$path) [IO.Path]::GetRelativePath($root, $path).Replace('\', '/') }
$records = foreach ($match in $matches) {
  [PSCustomObject]@{
    gameIcon = & $relative $match.GameIconPath
    candidates = @($match.Candidates | ForEach-Object {
      [PSCustomObject]@{ skillIcon = & $relative $_.SkillIconPath; distance = [Math]::Round($_.Distance, 6) }
    })
  }
}
$report = [PSCustomObject]@{
  schemaVersion = 1
  method = 'alpha-trimmed, aspect-preserving 16x16 premultiplied RGBA normalized RMS distance; lower is more similar'
  skillIconCount = $skillFiles.Count
  gameIconCount = $gameFiles.Count
  topCandidatesPerGameIcon = $Top
  matches = @($records)
}
[IO.File]::WriteAllText($OutputPath, ($report | ConvertTo-Json -Depth 6), [Text.UTF8Encoding]::new($false))
$distances = @($records | ForEach-Object { $_.candidates[0].distance } | Sort-Object)
$cut = [Math]::Min(30, $distances.Count)
[PSCustomObject]@{
  report = (& $relative (Resolve-Path -LiteralPath $OutputPath).Path)
  skillIcons = $skillFiles.Count
  gameIcons = $gameFiles.Count
  lowestDistances = @($distances | Select-Object -First $cut)
} | ConvertTo-Json -Compress