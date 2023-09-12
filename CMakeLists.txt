cmake_minimum_required(VERSION 3.19)

include(CheckCCompilerFlag)

project(
	sospin
	VERSION 1.1.0
	DESCRIPTION "A Library to calculate the decomposition of the Yukawa interactions invariants on SO(2N) groups in terms of the SU(N) subgroup"
 	LANGUAGES CXX
)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# set CMAKE policy
cmake_policy(SET CMP0135 NEW)

# enable testing functionality
enable_testing()

find_package(Doxygen)
if(Doxygen_FOUND)
  add_subdirectory(doc)
else()
    message(STATUS "Doxygen not found, not building docs")
endif()

# let the preprocessor know about the system name
IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
  MESSAGE(STATUS "current platform: Linux ")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
  MESSAGE(STATUS "current platform: Windows")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
  MESSAGE(STATUS "current platform: FreeBSD")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
  MESSAGE(STATUS "current platform: MacOS")
  set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE INTERNAL "" FORCE)
ELSE ()
  MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/out)
set(PROJECT_BUILD_DIR ${PROJECT_SOURCE_DIR}/build)

add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(test)  