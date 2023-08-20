# Doxygen


# set input and output files
set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.out)

# request to configure the file
configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
message("Doxygen build started")

set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_BUILTIN_STL_SUPPORT YES)

#doxygen_add_docs(docs modern/lib.hpp "${CMAKE_CURRENT_SOURCE_DIR}/mainpage.md"
#                 WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/include")
#
#doxygen_add_docs(docs modern/lib.hpp "
#                 WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

# Note: do not put "ALL" - this builds docs together with application EVERY TIME!
add_custom_target(docs ALL
   COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
   COMMENT "Generating API documentation with Doxygen"
   VERBATIM )
