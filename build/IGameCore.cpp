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

IGameCore::IGameCore(std::string fileName) : _fileName(fileName), _loaderGame(""), _loaderGraphics("")
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
        run();
    }
}

IGameCore::~IGameCore() {}

void IGameCore::run()
{
    _menu.loadScores();
    _menu.setLettersSize();
    loadGraphic(_menu.getIndexLib());
    while (_loop) {
        if (_menu.getInfoPlay()) {
            _state = GAME;
            _menu.setInfoPlay(false);
        }
        if (!_stateLoad && _state == GAME) {
            loadGraphic(_menu.getIndexLib());
            loadGame(_menu.getIndexGame());
            _stateLoad = true;
        }
        if (_state == MENU)
            _loop = loop(_menu);
        else if (_state == GAME)
            _loop = loop(*this->_loaderGame);
    }
}

bool IGameCore::loop(IGame &render) {
    std::string event;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    event = _loaderGraphics->handleEvent();
    if (event == "quit")
        return (false);
    if (event == "menu" && _state == GAME) {
        _state = MENU;
        return (true);
    }
    render.handleEvent(event);
    render.handleUpdate(time + std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - begin).count());
    render.handleRender(*this->_loaderGraphics);
    time += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - begin).count();
    if (event == "next_graphic" && _state == GAME)
        NextGraphic();
    if (event == "prev_graphic" && _state == GAME)
        PrevGraphic();
    if (event == "next_game" && _state == GAME)
        NextGame();
    if (event == "next_game" && _state == GAME)
        PrevGame();
    if (_state == GAME && !_loaderGame->getGameData().empty()) {
        if (_loaderGame->getGameData().find("go")->second == "yes") {
            _state = MENU;
            loadGraphic(_indexStart);
            _menu.resetMenu();
            _menu.setLettersSize();
            _stateLoad = false;
        }
    }
    return (true);
}

void IGameCore::loadGraphic(int index) {
    if (index == -1 || (size_t)index > _map_lib.size()) {
        return;
    }
    std::cout << _map_lib.at(index) << std::endl;
    _loaderGraphics.loadDotSo(_map_lib.at(index));
    _index_lib = index;
}

void IGameCore::loadGame(int index) {
    if (index == -1 || (size_t)index > _map_game.size())
        return;
    _loaderGame.loadDotSo(_map_game.at(index));
    _index_map = index;
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
    this->_index_lib += 1;
    if (_map_lib.size() > this->_index_lib)
        this->_index_lib = 0;
    _loaderGraphics.loadDotSo(_map_lib[this->_index_lib]);
}

void IGameCore::PrevGraphic()
{
    this->_index_lib -= 1;
    if (_map_lib.size() < this->_index_lib)
        this->_index_lib = _map_lib.size();
    _loaderGraphics.loadDotSo(_map_lib[this->_index_lib]);
}

void IGameCore::NextGame()
{
    // _loaderGame.loadDotSo(this->_map_game[this->_map_game_name[this->_index_lib + 1]]);
}

void IGameCore::PrevGame()
{
    // _loaderGame.loadDotSo(this->_map_game[this->_map_game_name[this->_index_lib - 1]]);
}

void IGameCore::quit()
{
    this->_quit = true;
}