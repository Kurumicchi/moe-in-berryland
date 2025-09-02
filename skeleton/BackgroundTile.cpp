#include "BackgroundTile.h"

BackgroundTile::BackgroundTile(float x, float y, float size, const sf::Texture* texture, const sf::IntRect& rect) {
    sprite.setTexture(*texture);
    sprite.setTextureRect(rect);
    sprite.setScale(size / 16.f, size / 16.f);
    sprite.setPosition(x, y);
}

void BackgroundTile::draw(sf::RenderTarget& target) const {
    target.draw(sprite);
}