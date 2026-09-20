# Docker Installation

The repository provides a ROS 2 Humble development container with an XFCE
desktop served by TigerVNC. The same Compose configuration supports macOS,
Windows, and Linux. The repository is mounted at `/workspace/rover_ws/src`, and
Docker volumes preserve the workspace's `build`, `install`, and `log`
directories between container recreations.

## Prerequisites

Install Docker:

- macOS and Windows: install
  [Docker Desktop](https://docs.docker.com/desktop/).
- Linux: install [Docker Engine](https://docs.docker.com/engine/install/) and
  the Docker Compose plugin. Configure Docker for use without `sudo`.

Install TigerVNC Viewer:

- macOS: `brew install --cask tigervnc-viewer`
- Windows: download TigerVNC from <https://tigervnc.org/>
- Linux: install the TigerVNC viewer package supplied by the distribution,
  such as `tigervnc-viewer` on Ubuntu.

The image uses the `linux/amd64` platform because ROS 2 Humble and its Gazebo
dependencies are consistently available for that architecture. Intel Macs and
typical Intel/AMD Windows and Linux hosts run it natively. Apple Silicon uses
Docker's amd64 emulation; in Docker Desktop, enable **Use Rosetta for
x86_64/amd64 emulation on Apple Silicon** under **Settings > General**.

### Windows 11 virtualization

Docker Desktop's WSL 2 backend requires hardware virtualization, **Virtual
Machine Platform**, and **Windows Subsystem for Linux**. Windows 11 Home is
supported; the full Hyper-V feature is not required.

Check **Task Manager > Performance > CPU > Virtualization**. If it reports
**Disabled**, enable Intel VT-x/Virtualization Technology or AMD-V/SVM in the
computer's BIOS/UEFI settings. If it reports **Enabled** but Docker says that
virtualization was not detected, run these commands from PowerShell as
Administrator:

```powershell
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
bcdedit.exe /set hypervisorlaunchtype auto
```

Restart Windows, then update and verify WSL:

```powershell
wsl --update
wsl --status
```

If Windows is itself a virtual machine, the host administrator must expose
nested virtualization. A managed school or work computer may require IT to
enable these features. See Docker's
[Windows requirements](https://docs.docker.com/desktop/setup/install/windows-install/)
and Microsoft's [WSL documentation](https://learn.microsoft.com/windows/wsl/faq)
for the current platform requirements.

## Clone the repository

Clone with submodules so the dependency manifests and vendored source packages
are available to the image build:

```bash
git clone --recurse-submodules https://github.com/RoboJackets/urc-software.git
cd urc-software
```

If the repository was cloned without submodules, initialize them before
building:

```bash
git submodule update --init --recursive
```

## Start the container

On macOS or Linux:

```bash
chmod +x setup.sh
./setup.sh start
```

On Windows PowerShell:

```powershell
.\setup.ps1 start
```

On Windows Command Prompt:

```bat
setup.bat start
```

The first build downloads ROS 2, XFCE, TigerVNC, and dependencies declared by
the repository's `package.xml` files. It can take several minutes, especially
under Apple Silicon emulation.

Connect TigerVNC Viewer to:

```text
localhost:5901
```

The default password is `ros`. Open **Terminal Emulator** in the XFCE desktop;
it starts at `/workspace/rover_ws`, with ROS 2 Humble and an existing workspace
install automatically sourced.

## Build the workspace

From Terminal Emulator inside the TigerVNC desktop:

```bash
colcon build --symlink-install
source install/setup.bash
```

If Docker has limited memory and a parallel build is killed, use Colcon's
sequential executor:

```bash
colcon build --symlink-install --executor sequential
```

To open the same container from a host terminal, use the platform's setup
script with the `shell` command:

```bash
./setup.sh shell
```

Use `.\setup.ps1 shell` or `setup.bat shell` on Windows.

## Stop and restart

On macOS or Linux:

```bash
./setup.sh stop
./setup.sh restart
```

The corresponding Windows commands are `.\setup.ps1 stop`,
`.\setup.ps1 restart`, `setup.bat stop`, and `setup.bat restart`. Stopping the
container does not remove the named workspace volumes.

## Configuration

Set these environment variables before starting the container when the defaults
need to change:

- `VNC_HOST_PORT` changes the host port from `5901`.
- `VNC_PASSWORD` changes the VNC password. TigerVNC uses at most eight
  characters.
- `VNC_GEOMETRY` changes the desktop size from `1280x800`.
- `VNC_DEPTH` changes the color depth from `24`.
- `ROS_DOMAIN_ID` changes the ROS domain from `0`.
- `VNC_BIND_ADDRESS` changes the bind address from `127.0.0.1`. Keep the
  localhost default unless remote VNC access is deliberately required.

For example, on macOS or Linux:

```bash
VNC_PASSWORD=rover VNC_GEOMETRY=1920x1080 ./setup.sh start
```

On PowerShell:

```powershell
$env:VNC_PASSWORD = "rover"
$env:VNC_GEOMETRY = "1920x1080"
.\setup.ps1 start
```

Rebuild the image after changing a `package.xml` so `rosdep` installs the new
dependency:

```bash
./setup.sh start
```

Use `./setup.sh logs` to inspect TigerVNC startup failures. To deliberately
delete the persistent build products as well as the container, run:

```bash
docker compose --project-name urc-software \
  --file docker/docker-compose.yml down --volumes
```
