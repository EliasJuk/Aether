@echo off
setlocal

for /F %%a in ('echo prompt $E ^| cmd') do set "ESC=%%a"
set "GREEN=%ESC%[92m"
set "CYAN=%ESC%[96m"
set "YELLOW=%ESC%[93m"
set "RED=%ESC%[91m"
set "RESET=%ESC%[0m"

echo %CYAN%============================================%RESET%
echo %CYAN% Aether - Run%RESET%
echo %CYAN%============================================%RESET%
echo.

REM Pasta onde este script esta: Aether\scripts
set "SCRIPT_DIR=%~dp0"
if "%SCRIPT_DIR:~-1%"=="\" set "SCRIPT_DIR=%SCRIPT_DIR:~0,-1%"

REM Raiz do projeto: Aether
for %%I in ("%SCRIPT_DIR%\..") do set "PROJECT_DIR=%%~fI"

set "BUILD_DIR=%PROJECT_DIR%\build"
set "EXE_NAME=Aether.exe"

cd /d "%PROJECT_DIR%"

echo Projeto: %PROJECT_DIR%
echo Build:   %BUILD_DIR%
echo.

if not exist "%BUILD_DIR%" (
  echo %RED%[ERRO]%RESET% Pasta build nao encontrada.
  echo Rode primeiro a opcao Build / Configurar CMake.
  pause
  exit /b 1
)

REM Caminhos comuns onde o CMake/Visual Studio pode gerar o executavel
set "EXE_PATH_1=%BUILD_DIR%\Debug\%EXE_NAME%"
set "EXE_PATH_2=%BUILD_DIR%\src\Debug\%EXE_NAME%"
set "EXE_PATH_3=%BUILD_DIR%\Game\Debug\%EXE_NAME%"
set "EXE_PATH_4=%BUILD_DIR%\Release\%EXE_NAME%"
set "EXE_PATH_5=%BUILD_DIR%\src\Release\%EXE_NAME%"
set "EXE_PATH_6=%BUILD_DIR%\Game\Release\%EXE_NAME%"

set "EXE_PATH="

if exist "%EXE_PATH_1%" set "EXE_PATH=%EXE_PATH_1%"
if "%EXE_PATH%"=="" if exist "%EXE_PATH_2%" set "EXE_PATH=%EXE_PATH_2%"
if "%EXE_PATH%"=="" if exist "%EXE_PATH_3%" set "EXE_PATH=%EXE_PATH_3%"
if "%EXE_PATH%"=="" if exist "%EXE_PATH_4%" set "EXE_PATH=%EXE_PATH_4%"
if "%EXE_PATH%"=="" if exist "%EXE_PATH_5%" set "EXE_PATH=%EXE_PATH_5%"
if "%EXE_PATH%"=="" if exist "%EXE_PATH_6%" set "EXE_PATH=%EXE_PATH_6%"

if "%EXE_PATH%"=="" (
  echo %RED%[ERRO]%RESET% Nao encontrei o executavel %EXE_NAME%.
  echo.
  echo Procurado em:
  echo   %EXE_PATH_1%
  echo   %EXE_PATH_2%
  echo   %EXE_PATH_3%
  echo   %EXE_PATH_4%
  echo   %EXE_PATH_5%
  echo   %EXE_PATH_6%
  echo.
  echo Rode primeiro:
  echo   Build / Configurar CMake
  echo   Compile / Compilar
  pause
  exit /b 1
)

REM Executa a partir da pasta do .exe
for %%I in ("%EXE_PATH%") do set "EXE_DIR=%%~dpI"

echo %GREEN%Executando %EXE_NAME%...%RESET%
echo %YELLOW%%EXE_PATH%%RESET%
echo.

cd /d "%EXE_DIR%"
"%EXE_PATH%"

echo.
echo %GREEN%Programa finalizado.%RESET%

endlocal
exit /b 0