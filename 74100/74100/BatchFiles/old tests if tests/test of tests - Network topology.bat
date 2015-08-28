@setlocal
@echo off

:MainFb
timeout /T 5 /NOBREAK

start /WAIT "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag timeout x100" 1 Networks/fb_z4_500.txt fb_z4 0 0 0 0 4
timeout /T 4 /NOBREAK

start /WAIT "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag timeout x100" 1 Networks/l_32x32.txt l 0 0 0 0 7
timeout /T 7 /NOBREAK

exit

start /WAIT "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag timeout x100" 1 Networks/bara.500.z4.links bara.z4 0 0 0.1 0.1 4
timeout /T 4 /NOBREAK

start /WAIT "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag timeout x100" 1 Networks/bara.500.z6.links bara.z6 0 0 0.1 0.1 5
timeout /T 5 /NOBREAK

start /WAIT "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag timeout x100" 1 Networks/bara.500.z8.links bara.z8 0 0 0.1 0.1 5
timeout /T 5 /NOBREAK

start /WAIT "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag timeout x100" 1 Networks/fb_z4_500.txt fb_z4 0 0 0.1 0.1 4
timeout /T 4 /NOBREAK

start /WAIT "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag timeout x100" 1 Networks/l_32x32.txt l 0 0 0.1 0.1 7
timeout /T 7 /NOBREAK


start /WAIT "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag timeout x100" 1 Networks/bara.500.z4.links bara.z4 0 0 0 0 4
timeout /T 4 /NOBREAK

start /WAIT "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag timeout x100" 1 Networks/bara.500.z6.links bara.z6 0 0 0 0 5
timeout /T 5 /NOBREAK

start /WAIT "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag timeout x100" 1 Networks/bara.500.z8.links bara.z8 0 0 0 0 5
timeout /T 5 /NOBREAK







exit

rem bara.500.z4.links bara.z4
rem fb_z4_500.txt fb_z4