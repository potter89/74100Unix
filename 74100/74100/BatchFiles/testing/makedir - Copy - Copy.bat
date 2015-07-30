@setlocal
@echo off



for /f "tokens=1,2,3,4,5,6,7,8,9,10* delims=_" %%a in ('dir /b Results\*.txt') do (

echo.%%b | findstr /C:"bara" 1>nul

if errorlevel 1 (
  set folderName=%%a__%%b_%%c_%%d__%%e__%%f__%%g__%%h__%%i
) ELSE (
  set folderName=%%a__%%b_%%c__%%d__%%e__%%f__%%g__%%h
)
goto break
)

:break
echo %folderName%
pause
exit