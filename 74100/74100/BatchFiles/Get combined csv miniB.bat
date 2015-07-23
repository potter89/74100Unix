@echo off
@setlocal EnableDelayedExpansion
@cd "C:\Users\Elvio A\Documents\GitHub\74100Unix\74100\74100\Release\Results"

if exist result.csv del result.csv
for %%f in (combOut_*.txt) do (
    set i=0
    for /F "delims=" %%l in (%%f) do (
        set /A i+=1
        set line!i!=%%l
    )
    echo %%f, !line1!, !line2!, !line3!, !line4!, !line5!, >> results.csv
)