@echo off
setlocal enabledelayedexpansion
set arquivo=output.exe

echo Removendo arquivo antigo..
del /f "%arquivo%" 2>nul
del /f *.o 2>nul

echo Compilando codigos...

set OBJETOS=
for %%f in (src\*.cpp) do (
    echo Compilando %%f...
    g++ -c "%%f" -I include -o "%%~nf.o"
    set OBJETOS=!OBJETOS! "%%~nf.o"
)

echo Linkando objetos...
g++ !OBJETOS! -o "%arquivo%"

echo Limpando arquivos temporarios...
del /f *.o 2>nul

echo.
echo Pronto! Executavel gerado: %arquivo%
"%arquivo%"

endlocal