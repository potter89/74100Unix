@setlocal
@echo off

set counter=100
set "projectPath=c:\Users\Elvio A\Documents\GitHub\74100Unix\74100\74100"
set tag=%1
set networkPath=%2
set networkType=%3
set generations=%4
set tauTag=%5
set tauStrat=%6
set noiseStrat=%7
set noiseTag=%8

rem echo deleted previous batchFiles
echo Y | DEL "%projectPath%\Release\Results\TempFiles\*.tmp"

:Main
for /F %%i in ('dir /b "%projectPath%\Release\Results\TempFiles\*.tmp"') do (
   echo Folder is NON empty
   timeout 2 /NOBREAK
   goto :Main
)

echo starting a new round
start "" "soloSim" %tag% %networkPath% %networkType% %generations% %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1.0
start "" "soloSim" %tag% %networkPath% %networkType% %generations% %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1.05
start "" "soloSim" %tag% %networkPath% %networkType% %generations% %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1.1
start "" "soloSim" %tag% %networkPath% %networkType% %generations% %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1.15
start "" "soloSim" %tag% %networkPath% %networkType% %generations% %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1.2
start "" "soloSim" %tag% %networkPath% %networkType% %generations% %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1.25
start "" "soloSim" %tag% %networkPath% %networkType% %generations% %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1.3
start "" "soloSim" %tag% %networkPath% %networkType% %generations% %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1.35
start "" "soloSim" %tag% %networkPath% %networkType% %generations% %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1.4
start "" "soloSim" %tag% %networkPath% %networkType% %generations% %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1.45
start "" "soloSim" %tag% %networkPath% %networkType% %generations% %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1.5
start "" "soloSim" %tag% %networkPath% %networkType% %generations% %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1.55
start "" "soloSim" %tag% %networkPath% %networkType% %generations% %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1.6
start "" "soloSim" %tag% %networkPath% %networkType% %generations% %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1.65
start "" "soloSim" %tag% %networkPath% %networkType% %generations% %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1.7
start "" "soloSim" %tag% %networkPath% %networkType% %generations% %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1.75
start "" "soloSim" %tag% %networkPath% %networkType% %generations% %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1.8
start "" "soloSim" %tag% %networkPath% %networkType% %generations% %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1.85
start "" "soloSim" %tag% %networkPath% %networkType% %generations% %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1.9
start "" "soloSim" %tag% %networkPath% %networkType% %generations% %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1.95
start /wait "" "soloSim" %tag% %networkPath% %networkType% %generations% %tauTag% %tauStrat% %noiseStrat% %noiseTag% 2.0
rem wait for the last one to finish

timeout 2 /NOBREAK

set /A counter=%counter%-1
if %counter%==0 goto ParseFolderName
goto Main


:ParseFolderName
rem this will make sure it wait for the last counter of sims finish
for /F %%i in ('dir /b "%projectPath%\Release\Results\TempFiles\*.tmp"') do (
   echo Folder is NON empty
   timeout 2 /NOBREAK
   goto :ParseFolderName
)

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

exit