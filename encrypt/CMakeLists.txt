

add_library(gc_encrypt SHARED base64.cc)

install(TARGETS gc_encrypt DESTINATION lib)