@setlocal
@echo off

:MainFb

start "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag timeout x100 STEALING MATRIX" 8 Networks/bara.1000.z4.links bara.z4 1 1 0 0 8
timeout /T 830 /NOBREAK

start "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag timeout x100 STEALING MATRIX" 8 Networks/bara.500.z8.links bara.z8 1 1 0 0 6
timeout /T 630 /NOBREAK

start "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag timeout x100 STEALING MATRIX" 8 Networks/bara.500.z6.links bara.z6 1 1 0 0 6
timeout /T 630 /NOBREAK

start "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag timeout x100 STEALING MATRIX" 8 Networks/bara.500.z4.links bara.z4 1 1 0 0 5
timeout /T 530 /NOBREAK

exit