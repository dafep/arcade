/*
** EPITECH PROJECT, 2020
** arcarde
** File description:
** main
*/

#include <iomanip>
#include <iostream>
#include <string>
#include <unistd.h>
#include "./header/IGameCore.hpp"

bool parsageArgument(std::string path)
{
    if(path.substr(path.find_last_of(".") + 1) == "so")
        return (true);
    return (false);
}

bool if_file_existe(std::string Filename)
{
    return access(Filename.c_str(), 0) == 0;
}

int usage(void)
{
    std::cerr << "USAGE:\n\t./arcade /lib/*.so" << std::endl;
    return (1);
}

int main(int ac, char **av)
{
    if (ac == 2 && parsageArgument(av[1]) == true) {
        IGameCore *core = new IGameCore(av[1]);
    } else {
        return (usage());
    }
}