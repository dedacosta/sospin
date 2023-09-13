include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
)

add_executable(SospinDListTest sospin_dlist_test.cpp)
target_include_directories(SospinDListTest
	PRIVATE ${gtest_SOURCE_DIR}/include
	PRIVATE ${gmock_SOURCE_DIR}/include
)
target_link_libraries(SospinDListTest PRIVATE sospin PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(SospinDListTest)