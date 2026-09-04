# ============================================================================
#  AKP ENGINE - 1-CLICK UNIVERSAL INSTALLER FOR WINDOWS (install.ps1)
#  Author: Akshar Miyani | AKP Studio
#  Usage: irm https://raw.githubusercontent.com/miyaniakshar1234/akp/main/install.ps1 | iex
# ============================================================================

$ErrorActionPreference = "Stop"

Write-Host "`n🚀 Installing AKP Flashy Development Toolkit (Author: Akshar Miyani)..." -ForegroundColor Cyan

$TargetDir = "$env:LOCALAPPDATA\include"
$AkpDir = "$TargetDir\akp"
New-Item -ItemType Directory -Force -Path $AkpDir | Out-Null

$RepoBase = "https://raw.githubusercontent.com/miyaniakshar1234/akp/main"

# Download amalgamated single header
$AkpHeaderUrl = "$RepoBase/include/akp.h"
Invoke-WebRequest -Uri $AkpHeaderUrl -OutFile "$TargetDir\akp.h"
Invoke-WebRequest -Uri $AkpHeaderUrl -OutFile "$AkpDir\akp.h"

# Configure CPATH and INCLUDE for GCC/Clang/MSVC
$CurrentCPath = [Environment]::GetEnvironmentVariable("CPATH", "User")
if ($CurrentCPath -notlike "*$TargetDir*") {
    $NewCPath = if ($CurrentCPath) { "$CurrentCPath;$TargetDir" } else { $TargetDir }
    [Environment]::SetEnvironmentVariable("CPATH", $NewCPath, "User")
}

$CurrentInclude = [Environment]::GetEnvironmentVariable("INCLUDE", "User")
if ($CurrentInclude -notlike "*$TargetDir*") {
    $NewInclude = if ($CurrentInclude) { "$CurrentInclude;$TargetDir" } else { $TargetDir }
    [Environment]::SetEnvironmentVariable("INCLUDE", $NewInclude, "User")
}

Write-Host "✔ AKP Engine successfully installed to: $TargetDir" -ForegroundColor Green
Write-Host "⚡ You can now use: #include <akp.h> or #include <akp/akp.h> in ANY C/C++ project!" -ForegroundColor Yellow
Write-Host "   Engineered by Akshar Miyani.`n" -ForegroundColor Cyan
