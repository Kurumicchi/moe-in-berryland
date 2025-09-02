#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "constants.h"

class Menu_State : public State
{
public:
    Menu_State();

    void handle_event(const sf::Event& event) override;
    void update() override;
    void render(sf::RenderTarget& target) override;
    int get_next_state() override;

private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture bgTexture;
    sf::Sprite background;

    bool play; // Z to start
};