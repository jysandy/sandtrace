# Sandtrace
A recursive ray tracer written in C++.
This is the dev branch. Here you can see the latest code, but it is usually a work in progress and may not even build. If you want to see the latest working version, look at the master branch.


## Building	and running
- Install `CMake`, `vcpkg` and a C++ compiler. sandtrace was developed and tested with MSVC.
- `cmake --preset=default`
- `cmake --build build`
- `.\build\sandtrace.exe; Invoke-Item scene.png`