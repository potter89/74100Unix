@setlocal
@echo off



for /f "tokens=1,2,3,4,5,6,7* delims=_" %%a in ('dir /b Results\*.txt') do (

echo.%%b | findstr /C:"bara" 1>nul

if errorlevel 1 (
  echo %%a__%%b_%%c_%%d__%%e__%%f
) ELSE (
  echo %%a__%%b_%%c__%%d__%%e
)
goto break
)

:break
pause
exit