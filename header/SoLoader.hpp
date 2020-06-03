/*
** EPITECH PROJECT, 2020
** arcarde
** File description:
** SoLoader
*/

#include <iostream>
#include <exception>
#include <dlfcn.h>
#include "./Err.hpp"

#ifndef SOLOADER_HPP_
#define SOLOADER_HPP_

#include <string>
#include <dlfcn.h>
#include <iostream>

template <typename T>
class SoLoader {
public:
    SoLoader(const std::string &filename)
    {
        if (filename == "")
            return;
        this->_lib = dlopen(filename.c_str(), RTLD_LAZY);
        if (this->_lib == nullptr)
            throw std::exception();
        T *(*func)() = reinterpret_cast<T *(*)()>(dlsym(this->_lib, "entry"));
        if (func == nullptr)
            throw std::exception();
        this->_instance = func();
    }

    ~SoLoader() {
        if (this->_instance != nullptr)
            delete this->_instance;
        if (this->_lib != nullptr)
            dlclose(this->_lib);
    };

    void load(const std::string &filename)
    {
        if (this->_instance != nullptr)
            delete this->_instance;
        if (this->_lib != nullptr)
            dlclose(this->_lib);
        if (filename == "")
            return;
        this->_lib = dlopen(filename.c_str(), RTLD_LAZY);
        if (this->_lib == nullptr)
            throw std::exception();
        T *(*func)() = reinterpret_cast<T *(*)()>(dlsym(this->_lib, "entry"));
        if (func == nullptr)
            throw std::exception();
        this->_instance = func();
    }

    T *operator ->() const {
        if (!_instance)
            throw std::exception();
        return (this->_instance);
    }

    T &operator *() const {
        return (*this->_instance);
    }
private:
    void *_lib = nullptr;
    T *_instance = nullptr;
};

#endif /* !SOLOADER_HPP_ */