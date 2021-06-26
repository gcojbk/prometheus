
find_package(GTest REQUIRED)

file(GLOB test_src  testAll.cc testEncrypt.cc random.cc)

include_directories(${PROJECT_SOURCE_DIR}/src/encrypt
                    ${GTEST_INCLUDE_DIRS})

add_executable(testAll ${test_src})

target_link_libraries(testAll PRIVATE gc_encrypt ${GTEST_BOTH_LIBRARIES} ${CRYPTO} pthread)

install(TARGETS testAll DESTINATION bin)
