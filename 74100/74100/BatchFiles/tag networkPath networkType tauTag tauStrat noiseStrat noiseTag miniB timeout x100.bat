@cd "C:\Users\Elvio A\Documents\GitHub\74100Unix\74100\74100\Release"
@echo off

set counter=100
set tag=%1
set networkPath=%2
set networkType=%3
set tauTag=%4
set tauStrat=%5
set noiseStrat=%6
set noiseTag=%7
set timeout=%8

echo tag= %tag%
echo networkPath= %networkPath%
echo networkType= %networkType%
echo tauTag= %tauTag%
echo tauStrat= %tauStrat%
echo noiseStrat= %noiseStrat%
echo noiseTag= %noiseTag%

:Main
start "" 74100.exe %tag% %networkPath% %networkType% 10000 %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1 0 1.0 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 10000 %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1 0 1.25 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 10000 %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1 0 1.5 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 10000 %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1 0 1.75 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 10000 %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1 0 2.0 0 0 tds

TIMEOUT /T %timeout% /NOBREAK

set /A counter=%counter%-1
echo counter is %counter%

if %counter%==0 goto ParseFolderName
goto Main


:ParseFolderName
::does only one cycle of the loop, retreieves filename based on barabasi or other types
for /f "tokens=1,2,3,4,5,6,7,8,9,10* delims=_" %%a in ('dir /b Results\*.txt') do (

echo.%%b | findstr /C:"bara" 1>nul

if errorlevel 1 (
  set folderName=%%a__%%b_%%c_%%d__%%e__%%f__%%g__%%h__%%i
) ELSE (
  set folderName=%%a__%%b_%%c__%%d__%%e__%%f__%%g__%%h
)
goto MoveFiles
)

:MoveFiles
md ".\Results\%folderName%"
move /-y ".\Results\*.txt" ".\Results\%folderName%\"

exit