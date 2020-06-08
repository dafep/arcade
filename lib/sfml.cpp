#include "../header/sfml.hpp"

Sfml::Sfml() {
    window.create(sf::VideoMode(800, 600, 60), "Arcade");
}

extern "C" {
    IGraphic *entry() {
        return new Sfml();
    }
}