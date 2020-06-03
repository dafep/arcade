/*
** EPITECH PROJECT, 2020
** arcarde
** File description:
** IGameCore
*/

#include "../header/IGameCore.hpp"
#include <map>
#include <dirent.h>
#include <string.h>
#include <vector>

IGameCore::IGameCore(std::string fileName) : _fileName(fileName), _loaderGame(nullptr), _loaderGraphics(nullptr)
{

    if (!(_fileName.rfind("./", 0) == 0))
        _fileName = "./" + _fileName;
    fill_map("./lib/");
    fill_map("./games/");

    for (auto it = 0; it < _map_lib.size(); it++) {
        if (_map_lib[it] == _fileName) {
            this->_path = _map_lib[it];
            this->_index_lib = it;
            this->_index_map = it;
            this->_knowLib = true;
            break;
        }
    }
    if (!_knowLib) {
        std::cerr << "oh shit the .so you tried to load doesn't exist" << std::endl << std::endl;
        std::cerr << "existing .so:" << std::endl;
        std::cerr << "\t- ./lib/lib_arcade_ncurse.so" << std::endl;
        std::cerr << "\t- ./lib/lib_arcade_sfml.so" << std::endl;
    } else {
        _ptr["SetNx_gr"] = &IGameCore::NextGraphic;
        _ptr["SetPr_gr"] = &IGameCore::PrevGraphic;
        _ptr["SetNx_gm"] = &IGameCore::NextGame;
        _ptr["SetPr_gm"] = &IGameCore::PrevGame;
        _ptr["qt"] = &IGameCore::quit;
        _ptr["mn"] = &IGameCore::loadMenu;
        run();
    }
}

IGameCore::~IGameCore() {}

void IGameCore::run()
{
    _loaderGraphics->load(_map_lib[this->_index_lib]);
}

void IGameCore::fill_map(const std::string & path)
{
    DIR *dir;
    struct dirent *e;
    std::string use_lib;

    if ((dir = opendir(path.c_str())) != NULL) {
        for (auto i = 0; (e = readdir(dir)) != NULL; i += 1) {
            if (e->d_name[0] != '.') {
                path == "./lib/" ?
                    this->_map_lib.push_back(path + e->d_name)
                :
                    this->_map_game.push_back(path + e->d_name);
            }
        }
        closedir(dir);
    } else {
        std::cerr << "Oh shit there's no such thing as a " << path << " directory." << std::endl;
        return;
    }
}

std::string IGameCore::extractLibName(const std::string & path)
{
    std::vector<std::string> tokens;
    std::string extract = ".so";
    size_t prev = 11;
    size_t pos = path.find(extract, prev);
    std::string token;

    do {
        if (pos == std::string::npos)
            pos = path.length();
        token = path.substr(prev, pos - prev);
        if (!token.empty())
            tokens.push_back(token);
        prev = pos + extract.length();
    } while (pos < path.length() && prev < path.length());

    return (tokens[0]);
}

void IGameCore::NextGraphic()
{
    // _loaderGraphics->load(this->_map_lib[this->_map_lib_name[this->_index_map + 1]]);
}

void IGameCore::PrevGraphic()
{
    // _loaderGraphics->load(this->_map_lib[this->_map_lib_name[this->_index_map - 1]]);
}

void IGameCore::NextGame()
{
    // _loaderGame->load(this->_map_game[this->_map_game_name[this->_index_lib + 1]]);
}

void IGameCore::PrevGame()
{
    // _loaderGame->load(this->_map_game[this->_map_game_name[this->_index_lib - 1]]);
}

void IGameCore::quit()
{
    this->_quit = true;
}

void IGameCore::loadMenu()
{

}