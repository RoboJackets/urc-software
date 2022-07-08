# Building and Testing:

```bash
colcon build
```

Invokes the build tool colcon, which calls the CMake build system files in each package (a.k.a. directory). CMake does build magic™ that automatically finds and installs necessary packages so your code is ready to run. 
ONLY RUN THIS COMMAND IN /colcon-urc!

If you get errors from CMake or XML —> build errors
Solution: Make sure all dependencies are installed

If you get errors from #include statements —> linker errors
Solution: Make sure to include and bind any necessary packages in CMake/XML

If you get errors from .cpp/.hpp/.py files —> compile-time errors
Solution: Check for typos and incorrect method usage

---
```bash
colcon build –packages-select <name of package>
```
Builds a specific package

---
```bash
colcon test
```

Runs tests on all built packages

---
```bash
colcon test-result --verbose
```

Outputs a detailed log of everything that happened during testing to your terminal

---
```bash
colcon build && colcon test && colcon test-result --verbose
```

Builds, tests, and shows you the results of all tests. Use this for day to day ROS2 development!

<hr style="border:1px solid grey">

# Launching the Simulation:

```bash
. install/setup.bash
```

Adds all required elements to your path, always run before launching anything

```bash
ros2 launch <directory with launch file> <python launch file>
```

Activates a launch file, boots up gazebo and the simulation

```bash
ros2 topic list
```

Returns all active topics

```bash
ros2 topic echo <topic name>
```

Shows what is being published to a given topic

```bash
rosdep update && rosdep install –from-paths src –ignore-src -r -y
```

Initializes all rosdep packages, enabling CMake to integrate and use them

```bash
sudo apt-get install ros-humble-<package name>
```

Use this to install a specific rosdep package missing from the CMake

<hr style="border:1px solid grey">

# Git Commands:

```bash
git push
```

Pushes your changes to your branch.

I’d highly recommend using built-in Git integrations in your text editor of choice instead, but this is always an option for the Vim/Emacs chads out there.

```bash
git pull
```

Get the newest version of your branch.

You can use the flag --recursive-submodules if you’d like to update submodule content as well, since by default github ignores submodules with any commands you enter.

```bash
git commit -m “<Message describing your commit>”
```

Creates a snapshot of the changes you’ve made to the repo before you push. The -m flag allows you to include a message describing what the commit does. Do this before you push.

```bash
git add <filename>
```

Adds a file you changed to the staging area. You can also do git add . to stage all of the files from the current directory that you changed. This needs to be done before you do git commit.

```bash
git fetch
```

Dowloads commits, files, and references from a remote repository into your local repository.

If you’re unable to checkout to a new branch or having issues with the remote repository in general, try using this command.

```bash
git stash
```

Use to save your progress on a given branch before swapping

```bash
git stash pop
```

Use to restore previously stashed progress

```bash
git branch
```

See all local branches

```bash
git branch -r
```

See all remote branches

```bash
git checkout <name of branch>
```

Swap to a specific branch

```bash
git submodule sync
```

Updates submodule metadata (the URL you linked in .gitmodules)

```bash
git submodule update –init
```

Initializes and pulls any changes for every submodule. Use this if you are missing a specific submodule package during build!

<hr style="border:1px solid grey">

# Linting/Formatting:

```bash
ament_uncrustify –reformat
```

Automatically reformats all .cpp and .hpp files to ensure they match the rules laid out by ament_code_style.cfg

```bash
ament_<use tab complete to see all the options>
```

All the various linters called when colcon test runs
