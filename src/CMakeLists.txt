# SOURCES
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.cpp *.h *.hpp)

add_library(sospin STATIC ${SOURCES})
target_include_directories(sospin PRIVATE ${PROJECT_SOURCE_DIR}/src PUBLIC ${PROJECT_SOURCE_DIR}/include)

install(TARGETS sospin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)
