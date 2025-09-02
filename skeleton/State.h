#pragma once
#include <SFML/Graphics.hpp>

class State {
public:
    virtual ~State() = default;

    virtual void handle_event(const sf::Event& event) = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderTarget& target) = 0;
    virtual int get_next_state() = 0;
};