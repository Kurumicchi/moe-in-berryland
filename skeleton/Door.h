#pragma once
#include <SFML/Graphics.hpp>

class Door {
private:
    sf::Sprite sprite;
    const sf::Texture* texture;
    sf::IntRect textureRect;
    bool opened = false;

public:
    Door(float x, float y, float size, const sf::Texture* tex, const sf::IntRect& rect);

    void render(sf::RenderWindow& window);
    void draw(sf::RenderTarget& target) const;
    bool isNear(const sf::FloatRect& playerBounds) const;
    bool isOpened() const { return opened; }
    void open();
    sf::FloatRect getBounds() const;
};