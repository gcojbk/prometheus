
file(GLOB pool_src  mempool.cc threadpool.cc)

add_library(util_pool SHARED ${pool_src})

install(TARGETS util_pool DESTINATION lib)
