@cd "C:\Users\Elvio A\Documents\GitHub\74100Unix\74100\74100\Release"
@echo off

set tag=%1
set networkPath=%2
set networkType=%3
set generations=%4
set tauTag=%5
set tauStrat=%6
set noiseStrat=%7
set noiseTag=%8
set b=%9

echo tag= %tag%
echo networkPath= %networkPath%
echo networkType= %networkType%
echo generations= %generations%
echo tauTag= %tauTag%
echo tauStrat= %tauStrat%
echo noiseStrat= %noiseStrat%
echo noiseTag= %noiseTag%

echo spam > .\TempFiles\%b%.tmp

start /WAIT "" 74100.exe %tag% %networkPath% %networkType% %generations% %tauTag% %tauStrat% %noiseStrat% %noiseTag% 1 0 %b% 0 0 tds

echo Y | DEL .\TempFiles\%b%.tmp

exit