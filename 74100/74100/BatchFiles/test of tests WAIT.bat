@setlocal
@echo off

:Main

start /WAIT "" "tag networkPath networkType generations tauTag tauStrat noiseStrat noiseTag miniB x100" 8 Networks/bara.500.z4.links bara.z4 10000 1 1 0.5 0.5

exit