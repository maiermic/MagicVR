# How To Build

This document explains how to build and run the project.

## Prerequisites

You need to install a C++14 compiler (for example [gcc][gcc] or [clang][clang]),
[cmake][cmake] and [conan][conan]. You can install them using

```
sudo apt-get install g++ cmake python python-pip
pip install conan
```

Since not all dependencies are available on conan's repository, you have to
build OpenSG2, VRPN and inVRs from source
([see this description][dependency build instructions]).

[gcc]: https://gcc.gnu.org/
[clang]: http://clang.llvm.org/
[cmake]: https://cmake.org/
[conan]: https://www.conan.io/
[dependency build instructions]: https://github.com/maiermic/virtual-reality-project-linux-build-instructions

## Install Dependencies

Separate from the dependencies you have to build from source (OpenSG2, VRPN
and inVRs), you need to install the dependencies managed by conan.
You need to compile them properly. Otherwise, you may get errors
(like [this][undefined reference error]):

[undefined reference error]: http://stackoverflow.com/q/41408216/1065654

```
cd .conan
conan install -s build_type=Release -s compiler=gcc -s compiler.version=5.4 -s compiler.libcxx=libstdc++11 --build=missing
```

## Build

Run

```
./linux_desktop_compile
```

or if you are in the V2C (LRZ):

```
./linux_compile
```

### Note

You might need to tell *cmake* which compiler you are using:

```
export CC=clang
export CXX=clang++
```

If you use [Clion][Clion] and don't start it from
the shell you have to configure those environment variables in Clion (see
[How to add environment variables in Clion][environment variables in Clion]).
Delete Clion's build directory (e.g. `cmake-build-release`) after you changed
environment variables and run *Tools > CMake > Reload CMake Project*.

[Clion]: https://www.jetbrains.com/clion/
[environment variables in Clion]: http://stackoverflow.com/a/38874446/1065654



## Run

There are two CMake targets:

### MagicVR_desktop  

Use this outside of the V2C (LRZ). Run

```
./start_demo_desktop_Release
```

from the project root directory (has to be the working directory).
Otherwise, the models are not found and you see only black objects.

### MagicVR_cave

If you are in the V2C (LRZ) then run

```
./start_demo_cave_Release
```
