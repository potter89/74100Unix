@setlocal
@echo off

:MainFb

start "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag timeout x100" 8 Networks/bara.500.z4.links bara.z4 1 1 0 0 6
timeout /T 5560 /NOBREAK


exit