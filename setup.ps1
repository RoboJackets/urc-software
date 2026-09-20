param(
    [ValidateSet("start", "stop", "restart", "shell", "logs", "help")]
    [string]$Command = "start"
)

$ErrorActionPreference = "Stop"
Set-Location -Path $PSScriptRoot

$ComposeArguments = @(
    "compose",
    "--project-name", "urc-software",
    "--file", "docker/docker-compose.yml"
)

function Invoke-Compose {
    & docker @ComposeArguments @args
    if ($LASTEXITCODE -ne 0) {
        throw "Docker Compose failed with exit code $LASTEXITCODE."
    }
}

function Assert-Docker {
    if (-not (Get-Command docker -ErrorAction SilentlyContinue)) {
        throw "Docker is not installed or is not on PATH."
    }

    & docker compose version *> $null
    if ($LASTEXITCODE -ne 0) {
        throw "Docker Compose is unavailable. Install Docker Desktop."
    }
}

function Start-Container {
    Assert-Docker
    Write-Host "Building and starting the URC TigerVNC development container..."
    Invoke-Compose up --build --detach

    $VncPort = if ($env:VNC_HOST_PORT) { $env:VNC_HOST_PORT } else { "5901" }
    $VncPassword = if ($env:VNC_PASSWORD) { $env:VNC_PASSWORD } else { "ros" }

    Write-Host ""
    Write-Host "Container is running."
    Write-Host "TigerVNC address: localhost:$VncPort"
    Write-Host "TigerVNC password: $VncPassword"
    Write-Host "Open Terminal Emulator in the desktop to work in /workspace/rover_ws."
    Write-Host "Run '.\setup.ps1 shell' for a host-terminal shell in the container."
}

switch ($Command) {
    "start" { Start-Container }
    "stop" {
        Assert-Docker
        Invoke-Compose down
    }
    "restart" {
        Assert-Docker
        Invoke-Compose down
        Start-Container
    }
    "shell" {
        Assert-Docker
        Invoke-Compose exec urc-development bash
    }
    "logs" {
        Assert-Docker
        Invoke-Compose logs --follow
    }
    "help" {
        Write-Host "Usage: .\setup.ps1 [start|stop|restart|shell|logs|help]"
    }
}
