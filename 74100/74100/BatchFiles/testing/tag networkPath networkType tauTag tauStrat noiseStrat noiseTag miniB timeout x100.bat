@setlocal
@echo off

set counter=3
set releasePath="C:\Users\Elvio A\Documents\GitHub\74100Unix\74100\74100\Release\Results\TempFiles"

set tag=%1
set networkPath=%2
set networkType=%3
set generations=%4
set tauTag=%5
set tauStrat=%6
set noiseStrat=%7
set noiseTag=%8
set b=%9


echo starting...
start "" "%releasePath%\wat"
rem >nul 2>nul dir /a "%releasePath%\*" && (echo Files exist) || (echo No file found)
pause


echo Y | DEL %releasePath%\Results\TempFiles\*.tmp
echo deleted previous batchFiles

:Main
if not exist %releasePath%\Results\TempFiles\*.tmp goto StartProcesses
	echo waiting...
    @ping -n 5 127.0.0.1 > nul
goto Main

:StartProcesses
start "" "soloSim" %tag% %networkPath% %networkType% %generations% %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1.0
start "" "soloSim" %tag% %networkPath% %networkType% %generations% %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1.25
start "" "soloSim" %tag% %networkPath% %networkType% %generations% %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1.5
start "" "soloSim" %tag% %networkPath% %networkType% %generations% %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1.75
start "" "soloSim" %tag% %networkPath% %networkType% %generations% %tauTag% %tauStrat% %noiseStrat% %noiseTag% 2.0

set /A counter=%counter%-1
rem echo counter is %counter%

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
echo No|move /-y ".\Results\*.txt" ".\Results\%folderName%\"

exit