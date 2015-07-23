@setlocal
@echo off

start "" "tag networkPath type tau timeout x100 - tagsDist" 8 Networks/fb_z4_512.txt fb_z4 1 4
timeout /T 460 /NOBREAK



rem start "" "Get folder names"
rem timeout /T 4 /NOBREAK
rem start "" "Get combined csv"

exit

