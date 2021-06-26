#include <string>
#include <openssl/aes.h>
#include "aes_encrypt.h"


void AES::AES_SetKey(const char* key) {
    AES_set_encrypt_key(reinterpret_cast<const unsigned char*>(key), 128, &enc_key_);
    AES_set_decrypt_key(reinterpret_cast<const unsigned char*>(key), 128, &dec_key_);
}

std::string AES::AES_Encrypt(const char* input, int length) {
    int encode_len = (length + (16 - 1)) & ~(16 - 1);  // round up to multiple of 16
    std::string out;
    out.resize(encode_len);
    char* buffer = const_cast<char*>(input);
    buffer = reinterpret_cast<char*>(malloc(encode_len));
    memcpy(buffer, input, length);
    for (int i = length; i < encode_len; i++) {
        buffer[i] = padding_;
    }
    for (int i = 0; i < encode_len; i += AES_BLOCK_SIZE) {
        AES_ecb_encrypt(reinterpret_cast<const unsigned char*>(buffer + i), 
                        reinterpret_cast<unsigned char*>(out.data() + i), &enc_key_, AES_ENCRYPT);
    }
    free(buffer);
    return out;
}

std::string AES::AES_Decrypt(const unsigned char* input, int length) {
    std::string out;
    char* decode_buf = reinterpret_cast<char*>(malloc(length));
    for (int i = 0; i < length; i += AES_BLOCK_SIZE) {
        AES_ecb_encrypt(reinterpret_cast<const unsigned char*>(input + i), 
                        reinterpret_cast<unsigned char*>(decode_buf + i), &dec_key_, AES_DECRYPT);
    }
    for(int i = 0; i < length; i++) {
        if (decode_buf[i] != padding_) {
            out += decode_buf[i];
        }
    }
    free(decode_buf);
    return out;
}

