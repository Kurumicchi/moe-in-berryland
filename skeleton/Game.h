#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <map>

#include "State.h"

class Game {
public:
    Game(std::string const & title, unsigned width, unsigned height);
    void start();

private:
    sf::RenderWindow window;

    std::map<int, std::unique_ptr<State>> states;
    int current_state;

    bool running;

    sf::Clock clock;

    void handle_events();
    void delay(float frameTime);
};

#endif