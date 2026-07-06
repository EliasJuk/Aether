@echo off
setlocal

for /F %%a in ('echo prompt $E ^| cmd') do set "ESC=%%a"
set "GREEN=%ESC%[92m"
set "CYAN=%ESC%[96m"
set "YELLOW=%ESC%[93m"
set "RED=%ESC%[91m"
set "RESET=%ESC%[0m"

echo %CYAN%============================================%RESET%
echo %CYAN% Aether - Compile%RESET%
echo %CYAN%============================================%RESET%
echo.

set "PATH=%PATH%;C:\Program Files\CMake\bin"

REM Pasta onde este script esta: Aether\scripts
set "SCRIPT_DIR=%~dp0"
if "%SCRIPT_DIR:~-1%"=="\" set "SCRIPT_DIR=%SCRIPT_DIR:~0,-1%"

REM Raiz do projeto: Aether
for %%I in ("%SCRIPT_DIR%\..") do set "PROJECT_DIR=%%~fI"

set "BUILD_DIR=%PROJECT_DIR%\build"

cd /d "%PROJECT_DIR%"

echo Projeto: %PROJECT_DIR%
echo Build:   %BUILD_DIR%
echo.

where cmake >nul 2>nul
if errorlevel 1 (
  echo %RED%[ERRO]%RESET% CMake nao encontrado no PATH.
  echo Verifique se o CMake esta instalado.
  pause
  exit /b 1
)

if not exist "%BUILD_DIR%" (
  echo %RED%[ERRO]%RESET% Pasta build nao encontrada.
  echo Rode primeiro a opcao Build / Configurar CMake.
  pause
  exit /b 1
)

echo %YELLOW%[1/1]%RESET% Compilando...
echo.

cmake --build "%BUILD_DIR%" --config Debug

if errorlevel 1 (
  echo.
  echo %RED%[ERRO]%RESET% Falha ao compilar o projeto.
  pause
  exit /b 1
)

echo.
echo %GREEN%Compilacao concluida com sucesso.%RESET%

endlocal
exit /b 0