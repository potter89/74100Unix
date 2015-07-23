setlocal
@echo off


for /f "tokens=1,2,3,4,5,6,7* delims=_" %%a in ('dir /b *.txt') do (
::echo %%a
::echo %%b
::echo %%c
::echo %%d
::echo %%e
::echo %%f
rem echo %%g

set str1=%%b

::if %%b==fb echo %%a__%%b_%%c_%%d__%%e__%%e__%%f
if not x%str1:bara=%==x%str1% echo It contains bara
goto break
)

:break
TIMEOUT /T 300 /NOBREAK
exit