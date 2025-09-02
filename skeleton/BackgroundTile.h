#ifndef BACKGROUNDTILE_H
#define BACKGROUNDTILE_H

#include <SFML/Graphics.hpp>

class BackgroundTile {
public:
    BackgroundTile(float x, float y, float size, const sf::Texture* texture, const sf::IntRect& rect);

    void draw(sf::RenderTarget& target) const;

private:
    sf::Sprite sprite;
};

#endif