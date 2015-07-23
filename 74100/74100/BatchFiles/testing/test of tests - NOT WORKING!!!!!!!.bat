@setlocal
@echo off

set tau=0
set inc=0.05
set stop=1+%inc%

:Main

start "" "tag networkPath type tau miniB timeout x100 - Copy" 8 Networks/bara.500.z4.links bara.z4 %tau% 3
timeout /T 10 /NOBREAK

set /A tau=%tau%+%inc%

if %tau%==%stop% exit

exit