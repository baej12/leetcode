# Build script for LeetCode helper tools
# PowerShell version

$CXX = "g++"
$CXXFLAGS = "-std=c++17", "-Wall", "-Wextra", "-O2"

function Build-All {
    Write-Host "Building all tools..." -ForegroundColor Cyan
    Build-Export
    Build-Get
    Build-Test
    Write-Host "[OK] All tools built successfully" -ForegroundColor Green
}

function Build-Export {
    Write-Host "Compiling export..." -ForegroundColor Cyan
    & $CXX @CXXFLAGS -o export.exe export.cpp
    Write-Host "[OK] export.exe built" -ForegroundColor Green
}

function Build-Get {
    Write-Host "Compiling get..." -ForegroundColor Cyan
    & $CXX @CXXFLAGS -o get.exe get.cpp
    Write-Host "[OK] get.exe built" -ForegroundColor Green
}

function Build-Test {
    Write-Host "Compiling test..." -ForegroundColor Cyan
    & $CXX @CXXFLAGS -o test.exe test.cpp
    Write-Host "[OK] test.exe built" -ForegroundColor Green
}

function Clean {
    Write-Host "Cleaning build artifacts..." -ForegroundColor Cyan
    Remove-Item -Path export.exe, get.exe, test.exe -ErrorAction SilentlyContinue
    Write-Host "[OK] Clean complete" -ForegroundColor Green
}

# Parse arguments
$command = if ($args.Count -eq 0) { "all" } else { $args[0] }

switch ($command) {
    "all" { Build-All }
    "export" { Build-Export }
    "get" { Build-Get }
    "test" { Build-Test }
    "clean" { Clean }
    "rebuild" { Clean; Build-All }
    default {
        Write-Host "Usage: .\build.ps1 [all|export|get|test|clean|rebuild]"
        exit 1
    }
}
