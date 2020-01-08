@echo off
gcc -o bin/test-%1 test/test-%1.c src/%1.c
bin\test-%1
