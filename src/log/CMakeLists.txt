
file(GLOB log_src log.cc)

include_directories(${PROJECT_SOURCE_DIR}/src/pattern)
                   
add_library(util_log SHARED ${log_src})

install(TARGETS util_log DESTINATION lib)
