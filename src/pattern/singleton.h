#ifndef UTIL_SINGLETON_H_
#define UTIL_SINGLETON_H_

template <typename T>
class Singleton
{
 public:
    static T& getInstance() {
        static T instance;
        return instance;
    }

 protected:
    Singleton()              = default;
    virtual ~Singleton()     = default;

 public:
    Singleton(T&&)           = delete;
    Singleton(const T&)      = delete;
    void operator=(const T&) = delete;
};

#endif // end of UTIL_SINGLETON_H_
