@echo off
setlocal

for /F %%a in ('echo prompt $E ^| cmd') do set "ESC=%%a"
set "GREEN=%ESC%[92m"
set "CYAN=%ESC%[96m"
set "YELLOW=%ESC%[93m"
set "RED=%ESC%[91m"
set "RESET=%ESC%[0m"

echo %CYAN%============================================%RESET%
echo %CYAN% Aether - Clean Rebuild%RESET%
echo %CYAN%============================================%RESET%
echo.

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

if exist "%BUILD_DIR%" (
  echo %YELLOW%[INFO]%RESET% Removendo pasta build...
  rmdir /s /q "%BUILD_DIR%"

  if exist "%BUILD_DIR%" (
    echo %RED%[ERRO]%RESET% Nao foi possivel remover a pasta build.
    pause
    exit /b 1
  )
) else (
  echo %YELLOW%[INFO]%RESET% Pasta build nao existe. Nada para remover.
)

echo.
echo %YELLOW%[1/3]%RESET% Configurando CMake...
call "%SCRIPT_DIR%\run-1-build.bat"

if errorlevel 1 (
  echo %RED%[ERRO]%RESET% Falha na etapa de build/configuracao.
  pause
  exit /b 1
)

echo.
echo %YELLOW%[2/3]%RESET% Compilando...
call "%SCRIPT_DIR%\run-2-compile.bat"

if errorlevel 1 (
  echo %RED%[ERRO]%RESET% Falha na etapa de compilacao.
  pause
  exit /b 1
)

echo.
echo %YELLOW%[3/3]%RESET% Executando...
call "%SCRIPT_DIR%\run-3-run.bat"

if errorlevel 1 (
  echo %RED%[ERRO]%RESET% Falha ao executar o programa.
  pause
  exit /b 1
)

echo.
echo %GREEN%Clean rebuild concluido com sucesso.%RESET%

endlocal
exit /b 0