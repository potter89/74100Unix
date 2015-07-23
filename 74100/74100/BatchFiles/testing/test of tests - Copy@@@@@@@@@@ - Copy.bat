@setlocal
@echo off

start "" "makedir" 8 Networks/bara.500.z4.links bara.z4 0 5
timeout /T 25 /NOBREAK
start "" "makedir" 8 Networks/l_3x3.txt l 0 4
timeout /T 10 /NOBREAK
start "" "makedir" 8 Networks/fb_z4_512.txt fb_z4 0 4
timeout /T 10 /NOBREAK
start "" "makedir" 8 Networks/fc_5.txt fc 0 4
exit