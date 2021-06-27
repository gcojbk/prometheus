
file(GLOB pool_src  mempool.cc threadpool.hpp)

include_directories(${PROJECT_SOURCE_DIR}/src/pattern)
                   
add_library(util_pool SHARED ${pool_src})

install(TARGETS util_pool DESTINATION lib)
