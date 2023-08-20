include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/include/sospin
  ${PROJECT_SOURCE_DIR}/src 
)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.cpp *.h *.hpp)

add_library(sospin STATIC ${SOURCES})