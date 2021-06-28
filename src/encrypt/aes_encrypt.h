#ifndef ENCRYPT_AES_H_
#define ENCRYPT_AES_H_

#include <openssl/aes.h>
#include <string>

class Aes {
public:
  Aes() = default;
  ~Aes() = default;

  void AES_SetKey(const char *key);
  std::string AES_Encrypt(const char *input, int length);
  std::string AES_Decrypt(const unsigned char *input, int length);

private:
  AES_KEY enc_key_;
  AES_KEY dec_key_;
  const char padding_ = 0;
};

#endif // end of ENCRYPT_AES_H_
