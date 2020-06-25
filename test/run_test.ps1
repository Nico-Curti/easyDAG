#!/usr/bin/env pwsh

Write-Host "Run testing" -ForegroundColor Yellow

./bin/test_math.exe

If ( -not $? )
{
  Write-Host "ERROR" -ForegroundColor Red
  exit 1
}

./bin/test_object.exe

If ( -not $? )
{
  Write-Host "ERROR" -ForegroundColor Red
  exit 1
}

./bin/test_utils.exe

If ( -not $? )
{
  Write-Host "ERROR" -ForegroundColor Red
  exit 1
}

Write-Host "PASSED" -ForegroundColor Yellow
