![Dynamic JSON Badge](https://img.shields.io/badge/dynamic/json?url=https%3A%2F%2Fraw.githubusercontent.com%2Fdedacosta%2Fsospin-dev%2Fdevelop%2Fpackage.json%3Ftoken%3DGHSAT0AAAAAACHJPDDUXSXAVSW5G4SKDDEGZH2LTKQ&query=version&label=Version&color=blue)
[![C++](https://img.shields.io/badge/C++-20-blue)](https://en.cppreference.com/w/cpp/20)
[![form](https://img.shields.io/badge/Form-4.3-blue)](https://github.com/vermaseren/form/tree/4.3)
[![DOI](https://zenodo.org/badge/DOI/10.1016/j.cpc.2016.01.010.svg)](https://doi.org/10.1016/j.cpc.2016.01.010)
[![DOI](https://img.shields.io/badge/arXiv-1509.00433-red)](https://arxiv.org/abs/1509.00433)

# ${\Large {\color{rgb(0,40,100}\textsf{SO}}\textsf{&#423;pin}}$ C++ Library

## Overview

The <span class="blue">SO</span><span class="reverse">S</span>pin(one reads it as a single word “sospin”) c++ library 
has the purpose to calculate the decomposition of the Yukawa interactions invariants on SO(2N) groups in terms
of the SU(N) subgroup. The program also includes specific functions to address the SO(10).

## Compilation & Installation

The ${\color{rgb(0,40,100}\textsf{SO}}\textsf{&#423;pin}$ library was converted into a *CMake* project.
This as simplified the installation of the library and  involves the followings commands 
1. cmake -S . -B build _(prepare the build)_
2. cmake --build build _(build the library and executables)_
3. cmake --install build _(by defaut installs in the *out* directory)_
4. make -f build/doc/Makefile doxygen-doc (optional, generate SOSpin library documentation)

For convenience, it was created Makefile with the goals: **clean** (removes build files), **install** (performs the cmake commands) and
**doxygen-doc** or **doc** generate the library documentation. This simplifies the set of the above commands.

During the build process, the folder **build** is created with all necessary tools for compilation without polluting the 
workspace. The installation of the library and in the include files are deployed in the generated folder **out**. This 
can be changed by setting the variable _CMAKE_INSTALL_PREFIX_ within the file **CMakeLists.txt** to the desired 
destination.

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
SOSpin library.


Linking code with the library in Linux:
g++ −O3 −I/library_installation_path/include −L/library_installation_path/lib \
example.cpp −o example −lsospin

Note: if you didn't use the --prefix option, the compilation will be more easy,
g++ -O3 example.cpp -o example -lsospin

and in the code use
#include <sospin/son.h>
and if using SO(10) specific functions:
#include <sospin/tools/so10.h>

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

## Bugs and remarks

For reporting bugs, asking questions, giving remarks and suggestions, we welcome you to use the [Issue Tracker](https://github.com/dedacosta/sospin/issues).

