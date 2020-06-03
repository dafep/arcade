/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include <string>
#include <map>
#include "./Graphic.hpp"

class IGame {
    public:
        virtual ~IGame() = default;
        virtual void handleEvent(const std::string &name) = 0;
        virtual void handleUpdate(int elepsedTime) = 0;
        virtual void handleRender(IGraphicRenderer &renderer) const = 0;
        virtual const std::map<std::string, std::string> getGameData() = 0;
};

#endif /* !IGAME_HPP_ */