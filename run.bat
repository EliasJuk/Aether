@echo off
setlocal

for /F %%a in ('echo prompt $E ^| cmd') do set "ESC=%%a"
set "GREEN=%ESC%[92m"
set "CYAN=%ESC%[96m"
set "YELLOW=%ESC%[93m"
set "RED=%ESC%[91m"
set "RESET=%ESC%[0m"

set "ROOT_DIR=%~dp0"
if "%ROOT_DIR:~-1%"=="\" set "ROOT_DIR=%ROOT_DIR:~0,-1%"

set "SCRIPTS_DIR=%ROOT_DIR%\scripts"

:menu
cls
echo %CYAN%============================================%RESET%
echo %CYAN% Aether - Menu de Scripts%RESET%
echo %CYAN%============================================%RESET%
echo.
echo %YELLOW%[0]%RESET% Setup
echo %YELLOW%[1]%RESET% Build / Configurar CMake
echo %YELLOW%[2]%RESET% Compile / Compilar
echo %YELLOW%[3]%RESET% Run / Executar
echo %YELLOW%[4]%RESET% Rebuild / Limpar e recompilar
echo %YELLOW%[5]%RESET% Quick / Build + Compile + Run
echo %YELLOW%[6]%RESET% Sair
echo.

choice /C 0123456 /N /M "Escolha uma opcao: "

if errorlevel 7 goto sair
if errorlevel 6 goto quick
if errorlevel 5 goto rebuild
if errorlevel 4 goto run
if errorlevel 3 goto compile
if errorlevel 2 goto build
if errorlevel 1 goto setup

:setup
call "%SCRIPTS_DIR%\run-0-setup.bat"
goto fim

:build
call "%SCRIPTS_DIR%\run-1-build.bat"
goto fim

:compile
call "%SCRIPTS_DIR%\run-2-compile.bat"
goto fim

:run
call "%SCRIPTS_DIR%\run-3-run.bat"
goto fim

:rebuild
call "%SCRIPTS_DIR%\run-4-rebuild.bat"
goto fim

:quick
call "%SCRIPTS_DIR%\run-quick.bat"
goto fim

:fim
echo.
echo %GREEN%Script finalizado.%RESET%
echo.
pause
goto menu

:sair
echo.
echo Saindo...
endlocal
exit /b 0