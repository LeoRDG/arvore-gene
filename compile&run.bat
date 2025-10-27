@echo off
setlocal enabledelayedexpansion

set "SRC_DIR=%USERPROFILE%\Desktop\git\arvore-gene"
set "OUT_FILE=%SRC_DIR%\output.exe"

echo Apagando executável antigo...
del /f /q "%OUT_FILE%" 2>nul

echo Compilando arquivos .cpp...
set "SRC_FILES="
for /r "%SRC_DIR%" %%f in (*.cpp) do (
    echo %%~nxf | findstr /i /c:"test.cpp" >nul
    if errorlevel 1 (
        set "SRC_FILES=!SRC_FILES! "%%f""
    )
)

g++ %SRC_FILES% -o "%OUT_FILE%"
if errorlevel 1 (
    echo ❌ Erro na compilação.
    exit /b 1
)

echo ✅ Compilação concluída. Executando programa...
"%OUT_FILE%"
