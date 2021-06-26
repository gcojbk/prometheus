
file(GLOB encrypt_src  base64_encode.cc aes_encrypt.cc)

add_library(util_encrypt SHARED ${encrypt_src})

target_link_libraries(util_encrypt PUBLIC ${CRYPTO})

install(TARGETS util_encrypt DESTINATION lib)
