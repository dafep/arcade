/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Ncurse
*/

#include <iostream>
#include "../header/Ncurse.hpp"

Ncurses::Ncurses() {
    initscr();
    start_color();
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();
    getmaxyx(stdscr, this->row, this->col);
    cbreak();
    timeout(1);
}

bool Ncurses::isOperational() {
    return isOpen;
}

std::string Ncurses::handleEvent() {
    int key = getch();
    if (key == ERR) {
        return "";
    } else {
        if (key == 27)
            return "menu";
        if (key == 'e')
            return "next_game";
        if (key == 'a')
            return "prev_game";
        if (key == 'x')
            return "next_graphic";
        if (key == 'w')
            return "prev_graphic";
        if (key == 10)
            return "enter";
        if (key == ' ')
            return "space";
        if (key == 'r')
            return "restart";
        if (key == 'z' || key == KEY_UP)
            return "up";
        if (key == 'q' || key == KEY_LEFT)
            return "left";
        if (key == 's' || key == KEY_DOWN)
            return "down";
        if (key == 'd' || key == KEY_RIGHT)
            return "right";
        if (key == 127 || key == KEY_DC) {
            isOpen = false;
            return "quit";
        }
    }
    return "";
}

void Ncurses::drawScreen() {
    refresh();
}

void Ncurses::clearScreen() {
    clear();
}

int Ncurses::getncursecolor(const AColor &color) {
    if (percent(color.getColorRed()) > 80 &&
    percent(color.getColorGreen()) > 80 &&
    percent(color.getColorBlue()) > 80) {
        return COLOR_WHITE;
    } else if (percent(color.getColorGreen()) < 80 &&
    percent(color.getColorRed()) < 80 &&
    percent(color.getColorBlue()) < 80) {
        return COLOR_BLACK;
    } else if (percent(color.getColorGreen()) < 80 &&
    percent(color.getColorRed()) > 80 &&
    percent(color.getColorBlue()) < 80) {
        return COLOR_RED;
    } else if (percent(color.getColorGreen()) > 80 &&
    percent(color.getColorRed()) < 80 &&
    percent(color.getColorBlue()) < 80) {
        return COLOR_GREEN;
    } else if (percent(color.getColorGreen()) < 80 &&
    percent(color.getColorRed()) < 80 &&
    percent(color.getColorBlue()) > 80) {
        return COLOR_BLUE;
    } else if (percent(color.getColorRed()) > 80 &&
    percent(color.getColorGreen()) > 80) {
        return COLOR_YELLOW;
    } else if (percent(color.getColorRed()) > 80 &&
    percent(color.getColorBlue()) > 80) {
        return COLOR_MAGENTA;
    } else if (percent(color.getColorGreen()) > 80 &&
    percent(color.getColorBlue()) > 80) {
        return COLOR_CYAN;
    } else {
        return COLOR_WHITE;
    }
}

int Ncurses::makeasquarepair(const Rect &rect)
{
    int i = 0;

    if (maxsquare == 0) {
        init_pair(i+100, getncursecolor(rect.getColor()), getncursecolor(rect.getColor()));
        contentj.push_back(getncursecolor(rect.getColor()));
        maxsquare++;
        return (0);
    }
    i = 1;
    for (; i < contentj.size(); i++)
        if (getncursecolor(rect.getColor()) == contentj[i])
            return (i+100);
    maxpairs++;
    init_pair(i+100, COLOR_BLACK, getncursecolor(rect.getColor()));
    contentj.push_back(getncursecolor(rect.getColor()));
    return (i);
}

int Ncurses::makeatextpair(const Text &text)
{
    int i = 0;

    if (maxpairs == 0) {
        init_pair(i, getncursecolor(text.getColor()), COLOR_BLACK);
        contenti.push_back(getncursecolor(text.getColor()));
        maxpairs++;
        return (0);
    }
    i = 1;
    for (; i < contenti.size(); i++)
        if (getncursecolor(text.getColor()) == contenti[i])
            return (i);
    maxpairs++;
    init_pair(i, getncursecolor(text.getColor()), COLOR_BLACK);
    contenti.push_back(getncursecolor(text.getColor()));
    return (i);
}

void Ncurses::drawSprite(const Sprite &sprite) {
}

void Ncurses::colors_text(char red, char blue, char green)
{
    if (red < 80 && green < 80 && blue < 80)
        attron(COLOR_PAIR(1));
    if (red > 80 && green < 80 && blue < 80)
        attron(COLOR_PAIR(9));
    if (red < 80 && green > 80 && blue < 80)
        attron(COLOR_PAIR(10));
    if (red < 80 && green < 80 && blue > 80)
        attron(COLOR_PAIR(11));
    if (red > 80 && green > 80)
        attron(COLOR_PAIR(12));
    if (red > 80 && blue > 80)
        attron(COLOR_PAIR(13));
    if (green > 80 && blue > 80)
        attron(COLOR_PAIR(14));
    if (red > 80 && green > 80 && blue > 80)
        attron(COLOR_PAIR(15));
}

void Ncurses::drawRect(const Rect &rect) {
    attron(COLOR_PAIR(makeasquarepair(rect)));
    for (size_t i = 0; i < rect.getSizeY(); i++) {
        for (size_t j = 0; j < rect.getSizeX(); j++) {
            mvprintw(static_cast<int>((rect.getPositionY() / 100 * 600) / (600 / 33)),
                     static_cast<int>((rect.getPositionX() / 100 * 800) / (800 / 88)),
                     "   ");
        }


    }
    attroff(COLOR_PAIR(makeasquarepair(rect)));
}

void Ncurses::drawCircle(const Circle &circle) {
}

void Ncurses::drawText(const Text &text) {
    attron(COLOR_PAIR(makeatextpair(text)));
    mvprintw(static_cast<int>((text.getPositionY() / 100 * 600) / (600 / 33)),
             static_cast<int>((text.getPositionX() / 100 * 800) / (800 / 88)),
             text.getText().c_str());
    attroff(COLOR_PAIR(makeatextpair(text)));
}

extern "C"
IGraphic *entry() {
    return new Ncurses();
}