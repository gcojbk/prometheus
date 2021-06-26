#ifndef ENCRYPT_AES_H_
#define ENCRYPT_AES_H_

#include <bits/stdc++.h>
#include <openssl/aes.h>

class AES {
 public:
    AES() = default;
    ~AES() = default;

    void AES_SetKey(const char* key);
    std::string AES_Encrypt(const char* input, int length);
    std::string AES_Decrypt(const unsigned char* input, int length);

 private:
    void AES_SetKey();

 private:
    AES_KEY enc_key_;
    AES_KEY dec_key_;
    const char padding_ = 0;
};

#endif // end of ENCRYPT_AES_H_