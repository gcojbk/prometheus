#include <gtest/gtest.h>
#include "base64_encode.h"
#include "aes_encrypt.h"

extern std::string randBinary(const int len);
extern std::string randStr(const int len);

TEST(test_base64, test_base64) {
    Base64 b64;
    for (int i = 0; i < 1000; i++){
        size_t len = rand() % 1000;
        std::string origin_str = randBinary(len);
        std::string enc_res = b64.Encode(reinterpret_cast<const unsigned char*>(origin_str.data()), origin_str.length());
        std::string dec_res = b64.Decode(enc_res.data(), enc_res.size());

        ASSERT_EQ(origin_str == dec_res, true);
        ASSERT_EQ(origin_str.size(), dec_res.size());
    }
}

TEST(test_aes, test_aes) {
    Aes aes;
    aes.AES_SetKey("testaes");
    for (int i = 0; i < 1000; i++){
        size_t len = rand() % 1000;
        std::string origin_str = randStr(len);
        std::string enc_res = aes.AES_Encrypt(origin_str.data(), origin_str.length());
        std::string dec_res = aes.AES_Decrypt(reinterpret_cast<const unsigned char*>(enc_res.data()), enc_res.size());

        ASSERT_EQ(origin_str == dec_res, true);
        ASSERT_EQ(origin_str.size(), dec_res.size());
    }
}

TEST(test_aes_base64, test_aes_base64) {
    Base64 b64;
    Aes aes;
    aes.AES_SetKey("testaes");
    for (int i = 0; i < 1000; i++){
        size_t len = rand() % 1000;
        std::string origin_str = randStr(len);
        std::string aes_enc_res = aes.AES_Encrypt(origin_str.data(), origin_str.length());
        std::string b64_enc_res = b64.Encode(reinterpret_cast<const unsigned char*>(aes_enc_res.data()), aes_enc_res.size());
        std::string b64_dec_res = b64.Decode(b64_enc_res.data(), b64_enc_res.size());
        std::string aes_dec_res = aes.AES_Decrypt(reinterpret_cast<const unsigned char*>(b64_dec_res.data()), b64_dec_res.size());

        ASSERT_EQ(origin_str == aes_dec_res, true);
        ASSERT_EQ(origin_str.size(), aes_dec_res.size());
    }
}
