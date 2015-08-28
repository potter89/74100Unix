@setlocal
@echo off

:MainFb

timeout /T 10 /NOBREAK



start "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag miniB timeout x100" 8 Networks/bara.500.z4.links bara.z4 1 1 0.1 0.1 3
timeout /T 320 /NOBREAK

start "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag miniB timeout x100" 1 Networks/bara.500.z4.links bara.z4 1 1 0.1 0.1 3
timeout /T 320 /NOBREAK

start "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag miniB timeout x100" 2 Networks/bara.500.z4.links bara.z4 1 1 0.1 0.1 3
timeout /T 320 /NOBREAK


start "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag miniB timeout x100" 8 Networks/fb_z4_500.txt fb_z4 1 1 0.1 0.1 2
timeout /T 220 /NOBREAK

start "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag miniB timeout x100" 1 Networks/fb_z4_500.txt fb_z4 1 1 0.1 0.1 2
timeout /T 220 /NOBREAK

start "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag miniB timeout x100" 2 Networks/fb_z4_500.txt fb_z4 5 1 0.1 0.1 2
timeout /T 220 /NOBREAK


start "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag miniB timeout x100" 8 Networks/bara.500.z4.links bara.z4 1 1 0.01 0.01 3
timeout /T 320 /NOBREAK

start "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag miniB timeout x100" 1 Networks/bara.500.z4.links bara.z4 1 1 0.01 0.01 3
timeout /T 320 /NOBREAK

start "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag miniB timeout x100" 2 Networks/bara.500.z4.links bara.z4 1 1 0.01 0.01 3
timeout /T 320 /NOBREAK


start "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag miniB timeout x100" 8 Networks/fb_z4_500.txt fb_z4 1 1 0.01 0.01 2
timeout /T 220 /NOBREAK

start "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag miniB timeout x100" 1 Networks/fb_z4_500.txt fb_z4 1 1 0.01 0.01 2
timeout /T 220 /NOBREAK

start "" "tag networkPath networkType tauTag tauStrat noiseStrat noiseTag miniB timeout x100" 2 Networks/fb_z4_500.txt fb_z4 5 1 0.01 0.01 2
timeout /T 220 /NOBREAK


exit