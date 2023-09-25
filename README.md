![Dynamic JSON Badge](https://img.shields.io/badge/dynamic/json?url=https%3A%2F%2Fraw.githubusercontent.com%2Fdedacosta%2Fsospin%2Fmain%2Fpackage.json&query=version&label=Version&color=blue)
[![C++](https://img.shields.io/badge/C++-11-blue)](https://en.cppreference.com/w/cpp/11)
[![form](https://img.shields.io/badge/Form-4.3-blue)](https://github.com/vermaseren/form/tree/4.3)
[![DOI](https://zenodo.org/badge/DOI/10.1016/j.cpc.2016.01.010.svg)](https://doi.org/10.1016/j.cpc.2016.01.010)
[![DOI](https://img.shields.io/badge/arXiv-1509.00433-red)](https://arxiv.org/abs/1509.00433)
<br/> <br/>

<img src="sospin.svg">

#  A C++ Library Project

## Overview

The ${\color{rgb(0,40,100)}\textsf{SO}}\textsf{&#423;pin}$ (one reads it as a single word “sospin”) c++ library 
has the purpose to calculate the decomposition of the Yukawa interactions invariants on SO(2N) groups in terms
of the SU(N) subgroup. The program also includes specific functions to address the SO(10).

For the original Git repository of the ${\color{rgb(0,40,100)}\textsf{SO}}\textsf{&#423;pin}$ library see [version 1.0.0](https://github.com/dedacosta/sospin/tree/v1.0.0).

## Compilation & Installation

The ${\color{rgb(0,40,100)}\textsf{SO}}\textsf{&#423;pin}$ library was converted into a *CMake* project.
This as simplified the installation of the library and  involves the followings commands 
1. cmake -S . -B build _(prepare the build)_
2. cmake --build build _(build the library and executables)_
3. cmake --install build _(by defaut installs in the *out* directory)_
4. make -f build/doc/Makefile doxygen-doc (optional, generate ${\color{rgb(0,40,100)}\textsf{SO}}\textsf{&#423;pin}$ library documentation)

For convenience, it was created Makefile with the goals:
```make 
    make clean|buid|install|doxygen-doc|doc|format|info
```
- **clean** -- it removes all generated build files and folders 
- **build** -- it builds the **cmake** project
- **install** -- it installs the executables, includes and library files in the **out** folder (if no other prefix is set) 
- **doxygen-doc** or **doc** -- it generates the library documentation with doxygen
- **format** -- it reformats the source and header files according to the configuration file _'.clang-format'_ 
- **info** -- it shows the header and source files being take into account by **cmake**

Without any given command, _make_ will build the workspace by default. This _Makefile_ is only meant to simplify the set
of the **cmake** commands shown above.

The code style follows the Google Style Guides (https://google.github.io/styleguide) and our extensions are encoded in 
_'.clang-format'_. The extended styling can be applied using git command:
```git 
     git clang-format
```

During the build process, the folder **build** is created with all necessary tools for compilation without polluting the 
workspace. The installation of the library and in the include files are deployed in the generated folder **out**. This 
can be changed by setting the variable _CMAKE_INSTALL_PREFIX_ within the file **CMakeLists.txt** to the desired 
destination.

The **CMake** build was test on:
- Linux 64-bits,
- macOS Ventura,
- Windows Visual Studio 17 2022,
- Windows MinGW64

## FORM Installation:

Symbolic Manipulation System FORM to final expression simplifications. The FORM version 4.3.1 has been successfully
tested The FORM binary package file can be downloaded in http://www.nikhef.nl/~form/, 
after accepting the license agreement.

After accepting the license agreement, click in binaries link and then click in 
the executable for your system:
- Linux 64-bits
- Apple

The other possibility to be used in other operating systems is to clone the git FORM project at 
[GitHub](https://github.com/vermaseren/form) and follow their Installation file.

There are two binaries for UNIX and Apple computers, one for sequential(form) 
and other for multi-threaded (tform).
You can choose anyone.
IMPORTANT: If you choose the multi-threaded version please rename the binary 
executable name to "form".

In UNIX you have to turn the execution flag on form,
chmod +x form

Uninstallation

To remove the installed library do: make uninstall
If you have installed the library in the system you also need to run the command 
with root privileges.

## Using the library and Compiling

Using the Library:
There are several code examples in the examples folder which come with the 
${\color{rgb(0,40,100)}\textsf{SO}}\textsf{&#423;pin}$ library.


Linking code with the library in Linux:
g++ −O3 −I/library_installation_path/include −L/library_installation_path/lib \
example.cpp −o example −lsospin

Note: if you didn't use the --prefix option, the compilation will be more easy,
g++ -O3 example.cpp -o example -lsospin

and in the code use
#include <sospin/son.h>
and if using SO(10) specific functions:
#include <sospin/tools/so10.h>

## Compilation within a Podman container

A **Dockerfile** is included to test the compilation process in a debian 12.1 container. A support script
at _./scripts/podman-box.sh_ was added to facilitate the container creation. The script has the following
commands
- **clean** -- it cleans the podman images and container
- **start/stop** -- it starts / stops the container

Without parameters the script makes a bash shell connection to the container.


## Using the specific functions or symbols within the constant part of Braket

    pure imaginary: i_
    delta function: d_(...,...)
    levi-civita tensor: e_(...,...,...)
    square root: sqrt(...)

## Quick examples

```sospin
#include <sospin/son.h>

using namespace sospin;
using namespace std;

int main(int argc, char ∗argv[ ]) {
    setDim(4) ;
    Braket left = bra(0, M(a), identity) ;
    left += bra(0, Mb(a) ∗ e_(l, m) / 2, b(m) ∗ b(l)) ;
    Braket right = ket(0, M(b), identity) ;
    right += ket(0,Mb(b) ∗ e_(i, j) / 2, bt(i) ∗ bt(j)) ;

    Braket res = left ∗ Bop() ∗ right ;
    res.evaluate(false) ;
    Field(M, 0, 0, ASYM_WITH_FLAVOR) ;
    Field(Mb, 0, 0, ASYM_WITH_FLAVOR) ;
    newId("a") ; newId("b") ;
    unsetFormIndexSum() ;
    CallForm(res, false, true, "j") ;
    res.setON() ;
    cout << "Result :" << endl << res << endl;
    res.setOFF() ;
    CleanGlobalDecl() ;
    exit(0) ;
}
```

## References

-  N. Cardoso, D. Emmanuel-Costa, N. Gonçalves, and C. Simões, “SO&#423;pin, a C++
  library for Yukawa decomposition in SO(2N) models,” [Comput. Phys. Commun.
  203 (2016) 178–200](https://doi.org/10.1016/j.cpc.2016.01.010), [arXiv:1509.00433](https://arxiv.org/abs/1509.00433) [hep-ph].
- ${\color{rgb(0,40,100)}\textsf{SO}}\textsf{&#423;pin}$ @ [Hepforge website](https://sospin.hepforge.org).
- ${\color{rgb(0,40,100)}\textsf{SO}}\textsf{&#423;pin}$ @ [Mendeley data](https://data.mendeley.com/datasets/w8g9349ppv/1)
## Bugs and remarks

For reporting bugs, asking questions, giving remarks and suggestions, we welcome you to use the [Issue Tracker](https://github.com/dedacosta/sospin/issues).

