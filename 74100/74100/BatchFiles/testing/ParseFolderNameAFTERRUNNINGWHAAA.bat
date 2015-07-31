
@cd "C:\Users\Elvio A\Documents\GitHub\74100Unix\74100\74100\Release"

for /f "tokens=1,2,3,4,5,6,7,8,9,10* delims=_" %%a in ('dir /b *.txt') do (
set folderName=%%a__%%b_%%c_%%d__%%e__%%f__%%g__%%h__%%i
::if not exist ".\Results\%folderName%" md ".\Results\%folderName%"
echo doing something
timeout 3
)


exit