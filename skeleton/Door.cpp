#include "Door.h"

Door::Door(float x, float y, float size, const sf::Texture* tex, const sf::IntRect& rect)
    : texture(tex), textureRect(rect)
{
    sprite.setTexture(*tex);
    sprite.setTextureRect(rect);
    sprite.setScale(size / 16.f, size / 16.f);
    sprite.setPosition(x, y);
}

void Door::render(sf::RenderWindow& window) {
    if (!opened)
        window.draw(sprite);
}

bool Door::isNear(const sf::FloatRect& playerBounds) const {
    return sprite.getGlobalBounds().intersects(playerBounds);
}

void Door::open() {
    opened = true;
}

sf::FloatRect Door::getBounds() const {
    return sprite.getGlobalBounds();
}

void Door::draw(sf::RenderTarget& target) const {
    if (!opened)
        target.draw(sprite);
}