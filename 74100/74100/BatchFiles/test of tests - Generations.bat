@setlocal
@echo off

:MainFb



start "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag miniB timeout x100 ZERO GENERATIONS" 8 Networks/bara.500.z4.links bara.z4 10 1 0 0 55
timeout /T 5560 /NOBREAK

start "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag miniB timeout x100 ZERO GENERATIONS" 8 Networks/bara.500.z4.links bara.z4 6 1 0 0 50
timeout /T 5060 /NOBREAK


start "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag miniB timeout x100 ZERO GENERATIONS" 8 Networks/bara.500.z4.links bara.z4 7 1 0 0 50
timeout /T 5060 /NOBREAK

start "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag miniB timeout x100 ZERO GENERATIONS" 8 Networks/bara.500.z4.links bara.z4 8 1 0 0 50
timeout /T 5060 /NOBREAK

start "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag miniB timeout x100 ZERO GENERATIONS" 8 Networks/bara.500.z4.links bara.z4 9 1 0 0 50
timeout /T 5060 /NOBREAK

exit