# Common Troubleshooting Issues
This guide is to help members quickly resolve issues with working with the codebase that have been encountered in the past.

* Could not find a package configuration file provided by "ament_cmake_core" or any other ament files...
For this, the package that is failing may not have listed another package as a dependency in the package.xml. Try adding that dependency and rebuilding so that CMake knows to build the other package first.
