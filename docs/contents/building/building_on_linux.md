---
layout: default
title: Building on Linux
parent: Building
grand_parent: Getting Started
nav_order: 2
---

# Build instructions for installing third-party dependencies (on Ubuntu Linux 20.04 LTS)

 - [C++ Compiler](#c-compiler)
 - [CMake](#cmake)
 - [Git](#git)
 - [Boost](#boost)
 - [NetCDF-cxx](#netcdf-cxx)
 - [MeshKernel](#meshkernel)
 - [PETSc](#petsc)
 - [Singularity](#singularity)
 - [Doxygen (optional, for building code documentation)](#doxygen)
 - [LaTeX (optional, for building the technical documentation)](#latex)

## C++ Compiler

### Installing the C++ (gcc) compiler on Linux (Ubuntu 20.04)

- `sudo apt update`
- `sudo apt install build-essential gdb`

---
## CMake
 
### Installing CMake on Linux (Ubuntu 20.04)

We cannot use the default version of CMake shipped with Ubuntu 20.04 as this version is too old. To manually install a newer version of CMake, follow these steps:

1. `sudo apt -y install libssl-dev`
2. `curl -L -O https://github.com/Kitware/CMake/releases/download/v3.22.3/cmake-3.22.3.tar.gz`
3. `tar -zxvf cmake-3.22.3.tar.gz`
4. `cd cmake-3.22.3`
5. `./bootstrap --prefix=/opt/cmake-3.22.3`
6. `make -j4`
7. `sudo make install`
8. `sudo ln -s /opt/cmake-3.22.3/bin/* /usr/local/bin/`

---
## Git

### Installing Git on Linux (Ubuntu 20.04)

Execute:
 1. `sudo apt update`
 2. `sudo apt install git`

---
## Boost

### Installing Boost on Linux (Ubuntu 20.04)

Follow these steps:
 1. `apt -y install curl`
 2. `curl -L -O https://boostorg.jfrog.io/artifactory/main/release/1.78.0/source/boost_1_78_0.tar.bz2`
 3. `tar jxf boost_1_78_0.tar.bz2`
 4. `sudo mkdir /opt/boost-1.78.0`
 5. `sudo chmod go+w /opt/boost-1.78.0`
 6. `cd boost_1_78_0`
 7. `./bootstrap.sh`
 8. `sudo ./b2 -j4 --prefix=/opt/boost-1.78.0 install`
 9. Add the following line to ~/.bashrc:
    `export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/boost-1.78.0/lib`

---
## NetCDF-cxx

### Installing NetCDF-cxx on Linux (Ubuntu 20.04)

Although NetCDF-cxx can be installed using apt on Ubuntu 20.04, we build it from source code because the apt package does not include CMake config files, so using it from our own CMake scripts would be cumbersome.  

The installation procedure is straightforward:

 1. Install NetCDF-c:  
	- `sudo apt -y install libnetcdf-dev`

 2. Clone, build and install NetCDF-cxx:
	- `git clone https://github.com/joostbonnet/netcdf-cxx4.git`
	- `cd netcdf-cxx4`
	- `git checkout feature/windows-dll` (Yes. Also on Linux.)
	- `mkdir build`
	- `cd build`
	- `cmake .. -DCMAKE_INSTALL_PREFIX=/opt/netcdf-cxx-4.3.2 -DCMAKE_BUILD_TYPE=Release`
	- `cmake --build . -j4`
	- `sudo cmake --build . --target install`

 3. Ensure that NetCDF-cxx can be found by cmake and the dynamic linker by adding these lines to e.g. your ~/.bashrc:
	- `export netCDFCxx_DIR=/opt/netcdf-cxx-4.3.2/lib/cmake/netCDF`
	- `export LD_LIBRARY_PATH=/opt/netcdf-cxx-4.3.2/lib:$LD_LIBRARY_PATH`

---
## MeshKernel

### Installing MeshKernel on Linux (Ubuntu 20.04)

1. Clone, build and install MeshKernel:
	- `git clone https://github.com/Deltares/MeshKernel.git`
	- `cd MeshKernel`
	- `mkdir build`
	- `cd build`
	- `cmake .. -DCMAKE_INSTALL_PREFIX=/opt/MeshKernel -DCMAKE_BUILD_TYPE=Release`
	- `cmake --build . -j4`
	- `cmake --build --target install`

2. Ensure that MeshKernel can be found by CMake and the dynamic linker by adding these lines to e.g. your ~/.bashrc:
	- `export LD_LIBRARY_PATH=/opt/MeshKernel/lib:$LD_LIBRARY_PATH`
	- `export MESHKERNEL_DIR=/opt/MeshKernel`


---
## PETSc

### Installing PETSc on Linux (Ubuntu 20.04)

 1. Install Intel oneAPI MPI:
    - `curl -L -O https://registrationcenter-download.intel.com/akdlm/irc_nas/18471/l_mpi_oneapi_p_2021.5.1.515_offline.sh`
    - `sudo sh l_mpi_oneapi_p_2021.5.1.515_offline.sh -a -s --eula accept`

 2. Install BLAS and LAPACK libraries (needed by petsc):
    - `sudo apt -y install libblas-dev liblapack-dev`

 3. Install petsc:
    - `curl -L -O https://ftp.mcs.anl.gov/pub/petsc/release-snapshots/petsc-3.16.4.tar.gz`
    - `tar zxf petsc-3.16.4.tar.gz`
    - `cd petsc-3.16.4`
    - `. /opt/intel/oneapi/setvars.sh`
    - `./configure --prefix=/opt/petsc-3.16.4 --with-mpi-dir=/opt/intel/oneapi/mpi/latest --with-fc=0 --with-debugging=0 --with-shared-libraries=1 --COPTFLAGS="-O3" --CXXOPTFLAGS="-O3"`
    - `make -j4`
    - `sudo make PETSC_DIR=$PWD PETSC_ARCH=arch-linux-c-opt install`
    - `make PETSC_DIR=/opt/petsc-3.16.4 PETSC_ARCH="" check`
    
 4. Ensure that petsc and the intel components can be found by CMake and the dynamic linker by adding these lines to e.g. your ~/.bashrc:
    - `source /opt/intel/oneapi/setvars.sh`
    - `export LD_LIBRARY_PATH=/opt/petsc-3.16.4/lib:$LD_LIBRARY_PATH`
    - `export PETSC_ROOT_DIR=/opt/petsc-3.16.4`

---
## Singularity

### Installing Singularity on Linux (Ubuntu 20.04)

Execute:
 - `wget -c https://github.com/sylabs/singularity/releases/download/v3.9.3/singularity-ce_3.9.3-focal_amd64.deb`
 - `sudo dpkg --install singularity-ce_3.9.3-focal_amd64.deb`

---
## Doxygen

### Installing Doxygen on Linux (Ubuntu 20.04)

First add the 'universe' repository:
 1. `sudo apt install -y software-properties-common`
 2. `sudo add-apt-repository universe`
 3. `sudo apt -y update`

Then install doxygen:

 4. `sudo apt-get -y install doxygen`

---
## LaTeX

### Installing

First add the 'universe' repository:
 1. `sudo apt install -y software-properties-common`
 2. `sudo add-apt-repository universe`
 3. `sudo apt -y update`

Then install TexLive:

 4. `sudo apt install texlive-full`

