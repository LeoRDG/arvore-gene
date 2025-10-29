@echo off
set arquivo=output.exe

echo Removendo arquivo antigo..
del /f "%arquivo%" 2>nul

echo Compilando codigo..
g++ src\*.cpp ^
 -I include ^
 -o "%arquivo%"

echo Pronto
"%arquivo%"
