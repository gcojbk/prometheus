#include <string>
#include "base64_encode.h"

std::string Base64::Encode (const unsigned char* in, int length) {
    int predict_len = (length + 2) / 3 * 4;
    int cnt = (length + 2) / 3 ;
    std::string encode_result;
    encode_result.reserve(predict_len);
    for (int i = 0; i < cnt - 1; i++) {
        encode_result += encode_table[in[0] >> 2];
        encode_result += encode_table[((in[0] & 0x03) << 4) + (in[1] >> 4)];
        encode_result += encode_table[((in[1] & 0x0f) << 2) + (in[2] >> 6)];
        encode_result += encode_table[in[2] & 0x3f];
        in += 3;
    }
    int last = length % 3;
    if (last == 1) {
        encode_result += encode_table[in[0] >> 2];
        encode_result += encode_table[((in[0] & 0x03) << 4)];
        encode_result += padding;
        encode_result += padding;
    } else if (last == 2) {
        encode_result += encode_table[in[0] >> 2];
        encode_result += encode_table[((in[0] & 0x03) << 4) + (in[1] >> 4)];
        encode_result += encode_table[((in[1] & 0x0f) << 2)];
        encode_result += padding;
    } else {
        encode_result += encode_table[in[0] >> 2];
        encode_result += encode_table[((in[0] & 0x03) << 4) + (in[1] >> 4)];
        encode_result += encode_table[((in[1] & 0x0f) << 2) + (in[2] >> 6)];
        encode_result += encode_table[in[2] & 0x3f];
    }
    return encode_result;
}

std::string Base64::Decode (const char* in, int length) {
    std::string result;
    if (length % 4 != 0) {
        return std::string("");
    }
    int cnt = length / 4;
    for (int i = 0; i < cnt - 1; i++) {
        result += static_cast<char>((decode_table[*in] << 2) + (decode_table[*(in+1)] >> 4));
        result += static_cast<char>(((decode_table[*(in+1)] & 0x0f) << 4) + (decode_table[*(in+2)] >> 2));
        result += static_cast<char>(((decode_table[*(in+2)] & 0x03) << 6) + (decode_table[*(in+3)]));
        in += 4;
    }
    result += static_cast<char>((decode_table[*in] << 2) + (decode_table[*(in+1)] >> 4));
    if (*(in + 2) != '=' && *(in + 3) != '=') {
        result += static_cast<char>(((decode_table[*(in+1)] & 0x0f) << 4) + (decode_table[*(in+2)] >> 2));
        result += static_cast<char>(((decode_table[*(in+2)] & 0x03) << 6) + (decode_table[*(in+3)]));
    } else if (*(in + 2) != '=' && *(in + 3) == '=') {
        result += static_cast<char>(((decode_table[*(in+1)] & 0x0f) << 4) + (decode_table[*(in+2)] >> 2));
    } 
    return result;
}
