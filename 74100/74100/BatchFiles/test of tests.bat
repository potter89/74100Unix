@setlocal
@echo off

:MainFb

start "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag miniB timeout x100" 2 Networks/bara.500.z4.links bara.z4 1 1 0 0 2
timeout /T 230 /NOBREAK

exit