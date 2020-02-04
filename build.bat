@echo off
gcc -shared -o bin/cstructures.dll src/*.c
mkdir bin\include 2>NUL
xcopy /s /y src\*.h bin\include >NUL
