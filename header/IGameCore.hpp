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
#include "./Menu.hpp"
#include <chrono>

#ifndef IGAMECORE_HPP_
#define IGAMECORE_HPP_

#define MENU 0
#define GAME 1

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
        void run();
        void loadGraphic(int index);
        void loadGame(int index);
        bool loop(IGame &render);

        SoLoader<IGraphic> _loaderGraphics;
        SoLoader<IGame> _loaderGame;
        IGraphic *_lgraph;
        Menu _menu;

        int _state = MENU;
        bool _loop = true;
        bool _stateLoad = false;
        int _indexStart = 0;
        int time = 0;

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