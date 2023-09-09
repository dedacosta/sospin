include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/include/sospin
  ${PROJECT_SOURCE_DIR}/src 
)

add_executable(so10_144 so10_144.cpp)
target_link_libraries(so10_144 PRIVATE sospin)
install(TARGETS so10_144 RUNTIME DESTINATION bin)

add_executable(so10_v1 so10_v1.cpp)
target_link_libraries(so10_v1 PRIVATE sospin)
install(TARGETS so10_v1 RUNTIME DESTINATION bin)

add_executable(so10_v2 so10_v2.cpp)
target_link_libraries(so10_v2 PRIVATE sospin)
install(TARGETS so10_v2 RUNTIME DESTINATION bin)

add_executable(so4 so4.cpp)
target_link_libraries(so4 PRIVATE sospin)
install(TARGETS so4 RUNTIME DESTINATION bin)

add_executable(so4_higherdim so4_higherdim.cpp)
target_link_libraries(so4_higherdim PRIVATE sospin)
install(TARGETS so4_higherdim RUNTIME DESTINATION bin)

