# cmake test
if(UNIX)    
    find_package(GTest REQUIRED)
	if (!GTEST_FOUND)
		message(FATAL_ERROR "googletest library is needed but can't be found")
	endif ()
    file(GLOB test_src *.cc)

    include_directories(${PROJECT_SOURCE_DIR}/src/encrypt
                        ${PROJECT_SOURCE_DIR}/src/pool
                        ${PROJECT_SOURCE_DIR}/src/pattern
                        ${GTEST_INCLUDE_DIRS})

    add_executable(Test ${test_src})

	link_directories(${GTEST_LIBRARY})
    target_link_libraries(Test PRIVATE util_encrypt util_pool ${GTEST_BOTH_LIBRARIES} ${CRYPTO} pthread)
endif()
