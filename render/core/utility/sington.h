#ifndef KRENDER_SINGTON_H
#define KRENDER_SINGTON_H

namespace krender
{
//lazy
    template<typename T>
    class Singleton{
    public:
        virtual ~Singleton() = default;
        T* Instance(){
            static T _instance;
            return &_instance;
        }
    private:
        Singleton() = default;
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;

    };
} // namespace krender
#endif