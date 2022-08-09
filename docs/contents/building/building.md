---
layout: default
title: Building Overview
parent: Building
grand_parent: Getting Started
nav_order: 1
has_children: false
---

# Build requirements

 - CMake 3.19.3 or higher
 - A C++17 compatible compiler
 - Git
 - Boost
 - NetCDF-cxx
 - MeshKernel
 - Petsc
 - Singularity (Linux only)
 - Doxygen (optional, for building code documentation)
 - LaTeX (optional, for building the technical documentation)

[Build instructions for installing third-party dependencies on Linux](./building_on_linux.md)

[Build instructions for installing third-party dependencies on Windows](./building_on_windows.md)

---
# Building instructions

## Building using an IDE

To use an IDE, such as Visual Studio:

```powershell
cmake -S . -B xbuild -G"Visual Studio 16 2019"
cmake --open xbuild
```

## Building using the command line

Configure step:
```powershell
cmake -S . -B build >> configure.log 2>&1
```

Build step (requires Doxygen, output in `build/docs/html`):
```powershell
cmake --build build >> build.log 2>&1
```

