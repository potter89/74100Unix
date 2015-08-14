@setlocal
@echo off

:MainFb

start "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag timeout x100" 1 Networks/bara.500.z4.links bara.z4 1 1 0 0 6
timeout /T 660 /NOBREAK

start "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag timeout x100" 8 Networks/bara.500.z4.links bara.z4 1 1 0 0 6
timeout /T 660 /NOBREAK

start "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag timeout x100" 1 Networks/fb_z4_512.txt fb_z4 1 1 0 0 6
timeout /T 660 /NOBREAK
s
start "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag timeout x100" 8 Networks/fb_z4_512.txt fb_z4 1 1 0 0 6
timeout /T 660 /NOBREAK

exit