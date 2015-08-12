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
start "" 74100.exe %tag% %networkPath% %networkType% 0 %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1 0 1.0 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 0 %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1 0 1.25 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 0 %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1 0 1.5 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 0 %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1 0 1.75 0 0 tds
start "" 74100.exe %tag% %networkPath% %networkType% 0 %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1 0 2.0 0 0 tds

TIMEOUT /T %timeout% /NOBREAK

set /A counter=%counter%-1
echo counter is %counter%

if %counter%==0 exit
goto Main