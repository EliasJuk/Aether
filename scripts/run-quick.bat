@echo off
setlocal

for /F %%a in ('echo prompt $E ^| cmd') do set "ESC=%%a"
set "GREEN=%ESC%[92m"
set "CYAN=%ESC%[96m"
set "YELLOW=%ESC%[93m"
set "RED=%ESC%[91m"
set "RESET=%ESC%[0m"

echo %CYAN%============================================%RESET%
echo %CYAN% Aether - Quick (Build + Compile + Run)%RESET%
echo %CYAN%============================================%RESET%
echo.

REM Pasta onde este script esta: Aether\scripts
set "SCRIPT_DIR=%~dp0"
if "%SCRIPT_DIR:~-1%"=="\" set "SCRIPT_DIR=%SCRIPT_DIR:~0,-1%"

REM Raiz do projeto: Aether
for %%I in ("%SCRIPT_DIR%\..") do set "PROJECT_DIR=%%~fI"

cd /d "%PROJECT_DIR%"

echo Projeto: %PROJECT_DIR%
echo Scripts: %SCRIPT_DIR%
echo.

echo %YELLOW%[1/3]%RESET% Configurando CMake...
call "%SCRIPT_DIR%\run-1-build.bat"

if errorlevel 1 (
  echo.
  echo %RED%[ERRO]%RESET% Falha na etapa Build / Configurar CMake.
  pause
  exit /b 1
)

echo.
echo %YELLOW%[2/3]%RESET% Compilando...
call "%SCRIPT_DIR%\run-2-compile.bat"

if errorlevel 1 (
  echo.
  echo %RED%[ERRO]%RESET% Falha na etapa Compile / Compilar.
  pause
  exit /b 1
)

echo.
echo %YELLOW%[3/3]%RESET% Executando...
call "%SCRIPT_DIR%\run-3-run.bat"

if errorlevel 1 (
  echo.
  echo %RED%[ERRO]%RESET% Falha na etapa Run / Executar.
  pause
  exit /b 1
)

echo.
echo %GREEN%Quick finalizado com sucesso.%RESET%

endlocal
exit /b 0