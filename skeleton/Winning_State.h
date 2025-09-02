#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>

class Winning_State : public State {
private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture bgTexture;
    sf::Sprite background;

public:
    Winning_State();
    void handle_event(const sf::Event& event) override;
    void update() override;
    void render(sf::RenderTarget& target) override;
    int get_next_state() override;
};