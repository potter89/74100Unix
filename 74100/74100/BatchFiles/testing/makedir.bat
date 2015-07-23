@cd "C:\Users\Elvio A\Documents\GitHub\74100Unix\74100\74100\Release"
@echo off

set counter=0
set tag=%1
set networkPath=%2
set networkType=%3
set tau=%4
set timeout=%5

:Main
start "" 74100.exe %tag% %networkPath% %networkType% 10000 %tau% 1 0 1.0 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 10000 %tau% 1 0 1.05 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 10000 %tau% 1 0 1.1 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 10000 %tau% 1 0 1.15 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 10000 %tau% 1 0 1.2 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 10000 %tau% 1 0 1.25 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 10000 %tau% 1 0 1.3 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 10000 %tau% 1 0 1.35 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 10000 %tau% 1 0 1.4 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 10000 %tau% 1 0 1.45 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 10000 %tau% 1 0 1.5 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 10000 %tau% 1 0 1.55 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 10000 %tau% 1 0 1.6 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 10000 %tau% 1 0 1.65 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 10000 %tau% 1 0 1.7 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 10000 %tau% 1 0 1.75 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 10000 %tau% 1 0 1.8 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 10000 %tau% 1 0 1.85 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 10000 %tau% 1 0 1.9 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 10000 %tau% 1 0 1.95 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 10000 %tau% 1 0 2.0 0 0 tds


TIMEOUT /T %timeout% /NOBREAK

set /A counter=%counter%+1
echo counter is %counter%

if %counter%==2 goto ParseFolderName
goto Main


:ParseFolderName
::does only one cycle of the loop, retreieves filename based on barabasi or other types
for /f "tokens=1,2,3,4,5,6,7* delims=_" %%a in ('dir /b Results\*.txt') do (

echo.%%b | findstr /C:"bara" 1>nul

if errorlevel 1 (
  set folderName=%%a__%%b_%%c_%%d__%%e__%%e__%%f
) ELSE (
  set folderName=%%a__%%b_%%c__%%d__%%e
)
goto MoveFiles
)

:MoveFiles
md ".\Results\%folderName%"
move /-y ".\Results\*.txt" ".\Results\%folderName%\"

exit