@echo off
setlocal

for /F %%a in ('echo prompt $E ^| cmd') do set "ESC=%%a"
set "GREEN=%ESC%[92m"
set "CYAN=%ESC%[96m"
set "YELLOW=%ESC%[93m"
set "RED=%ESC%[91m"
set "RESET=%ESC%[0m"

echo %CYAN%============================================%RESET%
echo %CYAN% Aether - Build (Configurar projeto)%RESET%
echo %CYAN%============================================%RESET%
echo.

set "PATH=%PATH%;C:\Program Files\CMake\bin"

REM Pasta onde este .bat esta: Aether\scripts
set "SCRIPT_DIR=%~dp0"
if "%SCRIPT_DIR:~-1%"=="\" set "SCRIPT_DIR=%SCRIPT_DIR:~0,-1%"

REM Raiz do projeto: Aether
for %%I in ("%SCRIPT_DIR%\..") do set "PROJECT_DIR=%%~fI"

set "BUILD_DIR=%PROJECT_DIR%\build"
set "VCPKG_TOOLCHAIN=C:\vcpkg\scripts\buildsystems\vcpkg.cmake"

cd /d "%PROJECT_DIR%"

echo Projeto: %PROJECT_DIR%
echo Build:   %BUILD_DIR%
echo.

if not exist "%VCPKG_TOOLCHAIN%" (
  echo %RED%[ERRO]%RESET% Nao encontrei o vcpkg em C:\vcpkg
  echo Verifique se o vcpkg esta instalado nesse caminho,
  echo ou edite a variavel VCPKG_TOOLCHAIN neste arquivo .bat.
  pause
  exit /b 1
)

if not exist "%BUILD_DIR%" (
  echo %YELLOW%[1/1]%RESET% Pasta build nao encontrada. Configurando o projeto...

  cmake -B "%BUILD_DIR%" -S "%PROJECT_DIR%" -DCMAKE_TOOLCHAIN_FILE="%VCPKG_TOOLCHAIN%"

  if errorlevel 1 (
    echo %RED%[ERRO]%RESET% Falha ao configurar o projeto com o CMake.
    pause
    exit /b 1
  )
) else (
  echo %GREEN%[1/1]%RESET% Projeto ja configurado. Pulando etapa.
)

echo.
echo %GREEN%Build configurado com sucesso.%RESET%
pause
endlocal