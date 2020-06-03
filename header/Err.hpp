/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Err
*/

#ifndef ERR_HPP_
#define ERR_HPP_

#include <string>

class Err : virtual public std::exception {
    public:
        std::string _error;
        Err(const std::string &error);
        ~Err();
        char const *what() const noexcept override {
            return _error.c_str();
        };
};

#endif /* !ERR_HPP_ */