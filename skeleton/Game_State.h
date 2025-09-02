#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "State.h"
#include "Player.h"
#include "Platform.h"
#include "Collectible.h"
#include "BackgroundTile.h"


class Game_State : public State {
public:
    Game_State();

    void handle_event(const sf::Event& event) override;
    void update() override;
    void render(sf::RenderTarget& target) override;
    int get_next_state() override;

private:
    sf::View camera;
    sf::Texture bgTexture;
    sf::Sprite background;
    sf::Vector2u textureSize;

    Player player;
    std::vector<Platform> platforms;

    // Collectibles
    int strawberryCount = 0;
    bool hasKey = false;

};

#endif