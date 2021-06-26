
add_library(gc_encrypt SHARED base64_encode.cc aes_encrypt.cc)

install(TARGETS gc_encrypt DESTINATION lib)
