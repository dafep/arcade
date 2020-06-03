/*
** EPITECH PROJECT, 2020
** arcarde
** File description:
** IGameCore
*/

#include <iomanip>
#include <iostream>
#include <string>
#include <map>
#include "./SoLoader.hpp"
#include "./Graphic.hpp"
#include "./IGame.hpp"
#include <vector>

#ifndef IGAMECORE_HPP_
#define IGAMECORE_HPP_


class IGameCore {
    public:
        explicit IGameCore(std::string fileName);
        ~IGameCore();
    private:
        void fill_map(const std::string & path);
        std::string extractLibName(const std::string & path);
        void setGraphics();
        void setGame();
        void NextGraphic();
        void PrevGraphic();
        void NextGame();
        void PrevGame();
        void quit();
        void loadMenu();
        void run();

        SoLoader<IGraphic> *_loaderGraphics;
        SoLoader<IGame> *_loaderGame;
        IGraphic *_lgraph;

        std::string _fileName;
        std::string _lib;
        std::string _path;
        std::vector<std::string> _map_lib;
        std::vector<std::string> _map_game;
        std::map<std::string, void (IGameCore::*)(void)> _ptr;
        bool _knowLib;
        bool _quit;
        int _index_map = -1;
        int _index_lib = -1;
};

#endif /* !IGAMECORE_HPP_ */