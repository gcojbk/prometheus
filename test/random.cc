#include <string>
#include <cstring>

static constexpr const char* alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+!@#$&*()_";

std::string randStr(const int len)
{
    std::string str;
    srand(time(NULL));
    for (int i = 0; i < len; ++i)
    {
        str += (alpha[rand() % strlen(alpha)]);
    }
    return str;
}

std::string randBinary(const int len)
{
    std::string str;
    srand(time(NULL));
    for (int i = 0; i < len; ++i)
    {
        str += (rand() % 256);
    }
    return str;
}
