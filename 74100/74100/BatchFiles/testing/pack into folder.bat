@setlocal
@echo off
set "projectPath=c:\Users\Elvio A\Documents\GitHub\74100Unix\74100\74100"

:ParseFolderName
echo combining
::does only one cycle of the loop, retreieves filename based on barabasi or other types
for /f "tokens=1,2,3,4,5,6,7,8,9,10* delims=_" %%a in ('dir /b "%projectPath%\Release\Results\*.txt"') do (

echo.%%b | findstr /C:"bara" 1>nul

if errorlevel 1 (
  set folderName=%%a__%%b_%%c_%%d__%%e__%%f__%%g__%%h__%%i
) ELSE (
  set folderName=%%a__%%b_%%c__%%d__%%e__%%f__%%g__%%h
)
goto MoveFiles
)

:MoveFiles

md "%projectPath%\Release\Results\%folderName%"
echo No|move /-y "%projectPath%\Release\Results\*.txt" "%projectPath%\Release\Results\%folderName%\"

echo moved to %folderName%
pause
exit