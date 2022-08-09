---
layout: default
title: Building on Windows
parent: Building
grand_parent: Getting Started
nav_order: 3
---

# Build instructions for installing third-party dependencies (on Windows)

 - [CMake](#cmake)
 - [Git](#git)
 - [Boost](#boost)
 - [NetCDF-cxx](#netcdf-cxx)
 - [MeshKernel](#meshkernel)
 - [PETSc](#petsc)
 - [Doxygen (optional, for building code documentation)](#doxygen)
 - [LaTeX (optional, for building the technical documentation)](#latex)

---
## CMake
 
### Installing CMake on Windows

Execute the following steps:
 1. Download CMake from https://github.com/Kitware/CMake/releases/download/ (minimal version 3.19)
 2. Follow the installation instructions, among others make sure to select the option below during installation:
 
 ![](images/cmake_installation.png)
 
 3. Install CMake for instance in `c:\Program Files\CMake\`
 4. Check whether the CMake-binary location has been added to the your system PATH:
    - Click the windows start button
    - Type `environment variables` to edit the System environment variables
    - Go to the settings field for Environment Variables
    - In the group System Variables: check that the PATH variable contains an entry containing your installation path:
      
      For the example above this should be:
       `c:\Program Files\CMake\bin`

---
## Git

### Installing Git under Windows

Download and install Git from https://git-scm.com/download/win
 
---
## Boost

### Installing Boost on Windows

Follow these steps:
 1. Download from https://sourceforge.net/projects/boost/: boost-binaries/1.78.0/boost_1_78_0-msvc-14.2-64.exe
 2. Install in `c:\boost\boost_1_78_0` or `c:\local\boost_1_78_0`
 3. Add environment parameters (not needed when boost was installed in `c:\local\boost_1_78_0`, CMake will find it there)
    - `BOOST_ROOT=c:\boost\boost_1_78_0`
    - `BOOST_INCLUDEDIR=c:\boost\boost_1_78_0`
    - `BOOST_LIBRARYDIR=c:\boost\boost_1_78_0\lib64-msvc-14.2`
 4. Add to environment `PATH: c:\boost\boost_1_78_0\lib64-msvc-14.2` or `PATH: c:\local\boost_1_78_0\lib64-msvc-14.2`

---
## NetCDF-cxx

### Installing NetCDF-cxx on Windows

On Windows, NetCDF-c and its dependencies must be built from source code. A Windows installer for NetCDF-c is available but the NetCDF-c installation that it provides does not satisfy all of the buildtime dependencies of NetCDF-cxx.

The installation takes a bit more time than on Ubuntu but is again straighforward. *Note that (at least) the install steps must be performed as Administrator for all packages!*

1. Download and unzip the source code for zlib, hdf5, curl and NetCDF-c:
	- https://zlib.net/zlib1211.zip
	- https://support.hdfgroup.org/ftp/HDF5/releases/hdf5-1.10/hdf5-1.10.8/src/hdf5-1.10.8.zip
	- https://curl.se/download/curl-7.81.0.zip
	- https://github.com/Unidata/netcdf-c/archive/refs/tags/v4.8.1.zip
	
2. Build zlib-1.2.11:
	- `mkdir zlib-1.2.11-build && cd zlib-1.2.11-build`
	- `cmake ..\zlib-1.2.11 -G "Visual Studio 16 2019"`
	- `cmake --build . -j4 --config Release`
	- `cmake --build . --config Release --target install`
	- `cd ..`

3. Build hdf5-1.10.8:
	- `mkdir hdf5-1.10.8-build && cd hdf5-1.10.8-build`
	- `cmake ..\hdf5-1.10.8 -G "Visual Studio 16 2019" -DHDF5_ENABLE_Z_LIB_SUPPORT=ON -DZLIB_DIR="C:\Program Files (x86)\zlib"`
	- `cmake --build . -j4 --config Release`
	- `cmake --build . --config Release --target install`
	- `cd ..`

4. Build curl-7.81.0
	- `mkdir curl-7.81.0-build && cd curl-7.81.0-build`
	- `cmake ..\curl-7.81.0 -G "Visual Studio 16 2019"`
	- `cmake --build . -j4 --config Release`
	- `cmake --build . --config Release --target install`
	- `cd ..`

5. Build NetCDF-c-4.8.1
	- `mkdir netcdf-c-4.8.1-build && cd netcdf-c-4.8.1-build`
	- `cmake ..\netcdf-c-4.8.1 -G "Visual Studio 16 2019" -DHDF5_DIR="C:\Program Files\HDF_Group\HDF5\1.10.8\share\cmake" -DZLIB_LIBRARY="C:\Program Files (x86)\zlib\lib\zlib.lib" -DCURL_LIBRARY="C:\Program Files (x86)\CURL\lib\libcurl_imp.lib" -DCURL_INCLUDE_DIR="C:\Program Files (x86)\CURL\include"`
	- `cmake --build . -j4 --config Release`
	- `cmake --build . --config Release --target install`
	- `cd ..`

	After installing NetCDF-c, find line 58 of `C:\Program Files (x86)\netCDF\lib\cmake\netCDF\netCDFTargets.cmake` and comment it out by placing a '#' character in front of it:
	
	`# INTERFACE_LINK_LIBRARIES "hdf5-shared;hdf5_hl-shared;C:/Program Files (x86)/zlib/lib/zlib.lib;C:\\Program Files (x86)\\CURL\\lib\\libcurl_imp.lib"`
	
	Neglecting to do this will cause build errors related to references to `hdf5-shared` and `hdf5_hl-shared` libraries (which do not exist) when building NetCDF-cxx.
	
6. Build NetCDF-cxx:
	- `git clone https://github.com/joostbonnet/netcdf-cxx4.git`
	- `cd netcdf-cxx4`
	- `git checkout feature/windows-dll`
	- `cd ..`
	- `mkdir netcdf-cxx4-build && cd netcdf-cxx4-build`
	- `cmake ..\netcdf-cxx4 -G "Visual Studio 16 2019" -DHDF5_DIR="C:\Program Files\HDF_Group\HDF5\1.10.8\share\cmake"`
	- `cmake --build . -j4 --config Release`
	- `cmake --build . --config Release --target install`
	- `cmake --build . -j4 --config Debug`
	- `cmake --build . --config Debug --target install`
	- `cd ..`

	Both Debug and Release builds of the libraries must be installed, otherwise debug builds of applications using NetCDF-cxx will link to the release libraries, which will result in heap corruption.

	After installing NetCDF-cxx, find line 58 of `C:\Program Files (x86)\NCXX\lib\cmake\netCDF\netcdf-cxx4Targets.cmake` and remove the text `;hdf5-shared`.

	Neglecting to do this will cause build errors related to references to an `hdf5-shared` library (which does not exist) when building software (using CMake) that depends on NetCDF-cxx.
	
7. Before running a project build, tell CMake where to find NetCDF-cxx and extend the Windows PATH:
	- `set netCDFCxx_DIR=C:\Program Files (x86)\NCXX\lib\cmake\netCDF`
	- `set PATH=%PATH%;C:\Program Files (x86)\NCXX\bin;C:\Program Files (x86)\netCDF\bin;C:\Program Files\HDF_Group\HDF5\1.10.8\bin;C:\Program Files (x86)\CURL\bin;c:\Program Files (x86)\zlib\bin`

---
## MeshKernel

### Installing MeshKernel on Windows

1. Clone, build and install MeshKernel:
	- `git clone https://github.com/Deltares/MeshKernel.git`
	- `cd MeshKernel`
	- `mkdir build`
	- `cd build`
	- `cmake .. -G "Visual Studio 16 2019"`
	- `cmake --build . -j4 --config Release`
	- `cmake --build . --config Release --target install`
	
2. Before running a project build, tell CMake where to find MeshKernel and extend the Windows PATH:
	- `set MESHKERNEL_DIR=C:\Program Files (x86)\MeshKernel`
	- `set PATH=%PATH%;C:\Program Files (x86)\MeshKernel\bin`

---
## PETSc

### Installing PETSc on Windows

1. Download and install Intel oneAPI MPI and MKL:
    - Download online or offline installers for MPI, MKL and optionally the Intel Fortran Compiler from the [standalone components](https://www.intel.com/content/www/us/en/developer/articles/tool/oneapi-standalone-components.html) page.
    - Run the installers. Installation takes some time.	

2. Install Cygwin:

    Download and install the Cygwin installer from http://www.cygwin.com/setup-x86_64.exe and run it to install Cygwin. Make sure the following Cygwin components are installed:
    - python3
    - make

3. Remove Cygwin link.exe:

    Cygwin link.exe can conflict with Intel ifort compiler. Run (from Cygwin terminal/bash-shell):

    - `mv /usr/bin/link.exe /usr/bin/link-cygwin.exe`

4. Setup Cygwin terminal/bash-shell with Working Compilers:

    - Run: Start -> All Programs -> Intel oneAPI 2021 -> Intel oneAPI Command Prompt for Intel64 for Visual Studio 2019
    - In this shell, run c:\cygwin64\bin\mintty.exe
    - In mintty, run /usr/bin/bash --login
    - Verify that the compilers are useable (by running `cl` and optionally `ifort` in this Cygwin terminal/bash-shell)

5. Download PETSc
    - Download and unzip https://ftp.mcs.anl.gov/pub/petsc/release-snapshots/petsc-3.16.5.tar.gz

6. Configure:

```bash
$ cd /cygdrive/c/Development/petsc-3.16.5

$ ./configure --prefix=/cygdrive/c/opt/petsc-3.16.5 \
    --with-cc='win32fe cl' --with-fc=0 --with-cxx='win32fe cl' \
    --with-mpi-include=['/cygdrive/c/Progra~2/Intel/oneAPI/mpi/latest/include','/cygdrive/c/Progra~2/Intel/oneAPI/mpi/latest/include/ilp64'] \
    --with-mpi-lib=['/cygdrive/c/Progra~2/Intel/oneAPI/mpi/latest/lib/release/impi.lib','/cygdrive/c/Progra~2/Intel/oneAPI/mpi/latest/lib/release/impicxx.lib'] \
    --with-mipexec=/cygdrive/c/Progra~2/Intel/oneAPI/mpi/latest/bin/mpiexec.exe \
    --with-blaslapack-dir=/cygdrive/c/Progra~2/Intel/oneAPI/mkl/latest/lib/intel64 \
    --with-debugging=0 -CFLAGS='-O2 -MD' -CXXFLAGS='-O2 -MD'
```

The above call to `configure` will cause PETSc to be built without Fortran bindings. If Fortran bindings are desired, replace `--with-fc=0` with `--with-fc='win32fe ifort'` (and be sure to have Intel oneAPI Fortran installed).

Spaces in paths cause 'configure' to fail. To find the DOS 8.3-style paths, use e.g.:

```bash
$ cygpath -u `cygpath -ms '/cygdrive/c/Program Files (x86)/Intel/oneAPI/mpi/latest/include'`
/cygdrive/c/PROGRA~2/Intel/oneAPI/mpi/latest/include
```

7. Build:
    - `make PETSC_DIR=/cygdrive/c/Development/petsc-3.16.5 PETSC_ARCH=arch-mswin-c-opt all`

8. Check:
    - `make PETSC_DIR=/cygdrive/c/Development/petsc-3.16.5 PETSC_ARCH=arch-mswin-c-opt check`

9. Install:
    - `make PETSC_DIR=/cygdrive/c/Development/petsc-3.16.5 PETSC_ARCH=arch-mswin-c-opt install`

---
## Doxygen

### Installing Doxygen on Windows

From https://www.doxygen.nl/download.html download the binary distribution for Windows.
At present it is `doxygen-1.9.3-setup.exe`

Follow the installation instructions.
CMake should be able to find Doxygen by itself.

---
## LaTeX

### Installing LaTeX on Windows

Download MiKTeX from https://miktex.org/download/ctan/systems/win32/miktex/setup/windows-x64/basic-miktex-21.12-x64.exe and install it as described on https://miktex.org/howto/install-miktex

Start the MiKTeX Console.
 - On the `Settings|General` tab, set the option to automatically install missing packages on-the-fly to `Always`.
 - On the `Settings|Directories` path, add `C:\ProgramData\MiKTex` to the TEXMF root directories.

Download ImageMagick from https://imagemagick.org .
Current version: https://download.imagemagick.org/ImageMagick/download/binaries/ImageMagick-7.1.0-19-Q16-HDRI-x64-dll.exe 
And run the installer. Be sure to select `install legacy utilities (e.g. 'convert')`, otherwise CMake will complain that it cannot find ImageMagick

