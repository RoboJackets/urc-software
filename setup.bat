@echo off
setlocal

cd /d "%~dp0"
set "COMMAND=%~1"
if "%COMMAND%"=="" set "COMMAND=start"

where docker >nul 2>nul
if errorlevel 1 (
  echo Docker is not installed or is not on PATH.
  exit /b 1
)

docker compose version >nul 2>nul
if errorlevel 1 (
  echo Docker Compose is unavailable. Install Docker Desktop.
  exit /b 1
)

if /i "%COMMAND%"=="start" goto start
if /i "%COMMAND%"=="stop" goto stop
if /i "%COMMAND%"=="restart" goto restart
if /i "%COMMAND%"=="shell" goto shell
if /i "%COMMAND%"=="logs" goto logs
if /i "%COMMAND%"=="help" goto help

echo Unrecognized command: %COMMAND%
goto help_error

:start
echo Building and starting the URC TigerVNC development container...
call :compose up --build --detach
if errorlevel 1 exit /b %errorlevel%
if "%VNC_HOST_PORT%"=="" set "VNC_HOST_PORT=5901"
if "%VNC_PASSWORD%"=="" set "VNC_PASSWORD=ros"
echo.
echo Container is running.
echo TigerVNC address: localhost:%VNC_HOST_PORT%
echo TigerVNC password: %VNC_PASSWORD%
echo Open Terminal Emulator in the desktop to work in /workspace/rover_ws.
echo Run 'setup.bat shell' for a host-terminal shell in the container.
exit /b 0

:stop
call :compose down
exit /b %errorlevel%

:restart
call :compose down
if errorlevel 1 exit /b %errorlevel%
goto start

:shell
call :compose exec urc-development bash
exit /b %errorlevel%

:logs
call :compose logs --follow
exit /b %errorlevel%

:help
echo Usage: setup.bat [start^|stop^|restart^|shell^|logs^|help]
exit /b 0

:help_error
echo Usage: setup.bat [start^|stop^|restart^|shell^|logs^|help]
exit /b 1

:compose
docker compose --project-name urc-software --file docker/docker-compose.yml %*
exit /b %errorlevel%
