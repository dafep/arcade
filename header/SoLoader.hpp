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

template <typename T>
class SoLoader {
    public:
        SoLoader &operator =(const SoLoader &) = delete;
        std::string _fileName;
        void *_lib = nullptr;
        T *_instance = nullptr;
        SoLoader(const std::string & fileName) {
            this->_fileName = fileName;
            this->_lib = nullptr;
            this->_instance = nullptr;
        }
        ~SoLoader() {
            if (this->_instance != nullptr)
                delete this->_instance;
            if (this->_lib != nullptr)
                dlclose(this->_lib);
        }
        void loadDotSo(std::string &fileName) {
            if (this->_instance != nullptr)
                delete this->_instance;
            if (this->_lib != nullptr)
                dlclose(this->_lib);
            this->_fileName = fileName;
            if ((this->_lib = dlopen(fileName.c_str(), RTLD_LAZY)) == nullptr)
                throw Err("Error load .so with error : " + std::string(dlerror()));
            T *(*func)() = reinterpret_cast<T *(*)()>(dlsym(this->_lib, "entry"));
            if (func == nullptr)
                throw Err("Error load .so with error : Unable find 'entry'");
            this->_instance = func();
        }

        T *operator -> () const {
            if (this->_instance == nullptr)
                throw "[SoLoader] _instance is null";
            return (this->_instance);
        }

        T &operator *() const {
            if (this->_instance == nullptr)
                throw "[SoLoader] _instance is null";
            return (*this->_instance);
        }

        std::string getPath() const {
            return (this->_fileName);
        }
};

#endif /* !SOLOADER_HPP_ */