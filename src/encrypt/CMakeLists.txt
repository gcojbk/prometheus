
file(GLOB encrypt_src  base64_encode.cc aes_encrypt.cc)

add_library(gc_encrypt SHARED ${encrypt_src})

target_link_libraries(gc_encrypt PUBLIC ${CRYPTO})

install(TARGETS gc_encrypt DESTINATION lib)
