/*
** EPITECH PROJECT, 2020
** arcarde
** File description:
** Graphic
*/

#ifndef GRAPHIC_HPP_
#define GRAPHIC_HPP_

#include <string>
#include "./draw.hpp"

class IGraphicRenderer
{
    public:
        virtual ~IGraphicRenderer() = default;
        virtual void drawScreen() = 0;
        virtual void clearScreen() = 0;
        virtual void drawRect(const Rect &rect) = 0;
        virtual void drawCircle(const Circle &circle) = 0;
        virtual void drawSprite(const Sprite &sprite) = 0;
        virtual void drawText(const Text &text) = 0;
        IGraphicRenderer &operator =(const IGraphicRenderer &) = delete;
};

class IGraphic: public IGraphicRenderer {
    public:
        IGraphic() = default;
        IGraphic(const IGraphic &) = delete;
        virtual ~IGraphic() = default;
        virtual bool isOperational() = 0;
        virtual std::string handleEvent() = 0;
};

#endif /* !GRAPHIC_HPP_ */