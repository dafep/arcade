/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Ncurse
*/

#ifndef NCURSE_HPP_
#define NCURSE_HPP_

#include "./Graphic.hpp"
#include <ncurses.h>
#include <vector>

#define percent(x) (x * 0.39)

class Ncurses : public IGraphic {
public:
    Ncurses();
    ~Ncurses() override = default;

    bool isOperational() override;
    std::string handleEvent() override;

    void drawScreen() override;
    void clearScreen() override;

    void drawRect(const Rect &rect) override;
    void drawCircle(const Circle &circle) override;
    void drawSprite(const Sprite &sprite) override;
    void drawText(const Text &text) override;

    int makeasquarepair(const Rect &rect);
    int makeatextpair(const Text &text);

    int getncursecolor(const AColor &color);

    void color_pair();
    void colors(char red, char blue, char green);
    void colors_text(char red, char blue, char green);

    int maxsquare = 0;
    int maxpairs = 0;
    std::vector<int>contenti;
    std::vector<int>contentj;
    bool isOpen = true;
    int row = 0;
    int col = 0;

    int x = 0;
    int y = 0;
    WINDOW *my_win;
};

#endif /* !NCURSE_HPP_ */