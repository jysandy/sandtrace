# sandtrace
A recursive ray tracer.

## Building	and running
- Install `CMake`, `vcpkg` and a C++ compiler. sandtrace was developed and tested with MSVC.
- `cmake --preset=default`
- `cmake --build build`
- `.\build\sandtrace.exe -s ".\scenes\scene1.json"; Invoke-Item scene.png`