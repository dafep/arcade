/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** sfml
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include "./Graphic.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Sfml : public IGraphic {
    public:
        Sfml();
        ~Sfml() override = default;
        bool isOperational() override;
        std::string handleEvent() override;
        void drawScreen() override;
        void clearScreen() override;
        void drawRect(const Rect &rect) override;
        void drawCircle(const Circle &circle) override;
        void drawSprite(const Sprite &sprite) override;
        void drawText(const Text &text) override;
        sf::RenderWindow window;
        bool isOpen = true;
};

#endif /* !SFML_HPP_ */