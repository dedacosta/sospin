cmake_minimum_required(VERSION 3.15)

project(
	sospin
	VERSION 1.0.1
	DESCRIPTION "A Library to calculate the decomposition of the Yukawa interactions invariants on SO(2N) groups in terms of the SU(N) subgroup"
 	LANGUAGES CXX
)
  
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_EXTENSIONS OFF)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE INTERNAL "" FORCE)

find_package(Doxygen)
if(Doxygen_FOUND)
  add_subdirectory(doc)
else()
    message(STATUS "Doxygen not found, not building docs")
endif()


#set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
#set(PROJECT_BUILD_DIR ${PROJECT_SOURCE_DIR}/build)
  
add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(test)  