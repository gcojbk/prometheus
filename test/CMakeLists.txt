
find_package(GTest REQUIRED)

file(GLOB test_src *.cc)

include_directories(${PROJECT_SOURCE_DIR}/src/encrypt
                    ${PROJECT_SOURCE_DIR}/src/pool
                    ${PROJECT_SOURCE_DIR}/src/pattern
                    ${GTEST_INCLUDE_DIRS})

add_executable(testAll ${test_src})

target_link_libraries(testAll PRIVATE util_encrypt util_pool ${GTEST_BOTH_LIBRARIES} ${CRYPTO} pthread)

install(TARGETS testAll DESTINATION bin)
