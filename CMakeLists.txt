cmake_minimum_required(VERSION 3.16)

include(CheckCCompilerFlag)
include(CMakeForceCompiler)

file(READ "package.json" json)
string(REGEX MATCH "\"version\": \"([\\.0-9]+)\"," _ ${json})
set(version ${CMAKE_MATCH_1})


# let the preprocessor know about the system name
IF (CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
  MESSAGE(STATUS "current platform: Linux ")
ELSEIF (CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
  MESSAGE(STATUS "current platform: Windows")
ELSEIF (CMAKE_HOST_SYSTEM_NAME MATCHES "FreeBSD")
  MESSAGE(STATUS "current platform: FreeBSD")
ELSEIF (CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
  MESSAGE(STATUS "current platform: MacOS")
  cmake_policy(SET CMP0135 NEW) # set CMAKE policy
  set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE INTERNAL "" FORCE)
ELSE ()
  MESSAGE(STATUS "other platform: ${CMAKE_HOST_SYSTEM_NAME}")
ENDIF (CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")

project(
	sospin
	VERSION ${version}
	DESCRIPTION "A Library to calculate the decomposition of the Yukawa interactions invariants on SO(2N) groups in terms of the SU(N) subgroup"
 	LANGUAGES CXX
)

message("Project: ${PROJECT_NAME} v${PROJECT_VERSION}")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# CXX Compiler configuration
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -pedantic -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# enable testing functionality
enable_testing()

find_package(Doxygen)
if(Doxygen_FOUND)
  add_subdirectory(doc)
else()
    message(STATUS "Doxygen not found, not building docs")
endif()

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/out)
set(PROJECT_BUILD_DIR ${PROJECT_SOURCE_DIR}/build)

add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(test)  