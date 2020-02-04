@echo off
call build.bat
gcc -o bin/test-%1 test/test-%1.c -L./bin -lcstructures
bin\test-%1
