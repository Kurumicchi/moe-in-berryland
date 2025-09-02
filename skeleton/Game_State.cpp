#include "Game_State.h"
#include "constants.h"
#include "Map.h"
#include "Door.h"
#include <iostream>

Game_State::Game_State() {
    // Load background
    if (!bgTexture.loadFromFile("assets/Bacground Cutee.PNG")) {
        std::cout << "Failed to load background\n";
    }
    background.setTexture(bgTexture);
    textureSize = bgTexture.getSize();

    // Generate platforms
    platforms = generate_platforms_from_map();

    // Set up view
    camera.reset(sf::FloatRect(0, 0, screen_width, screen_height));
}

// Handle events for the game state
void Game_State::handle_event(const sf::Event& event) {
    player.handleInput();
}

// Update the game state
void Game_State::update() {
    player.applyPhysics(); // Apply gravity and movement

    player.move(platforms); // Move Moe

    // Collision detection (feet-based)
    bool onPlatform = false;
    sf::FloatRect feetBounds = player.getFeetHitbox();

    for (const Platform& plat : platforms) {
        sf::FloatRect platformBounds = plat.getBounds();

        float feetBottom = feetBounds.top + feetBounds.height;
        float platformTop = platformBounds.top;

        bool isFeetOnPlatform =
            feetBounds.left < platformBounds.left + platformBounds.width &&
            feetBounds.left + feetBounds.width > platformBounds.left;

        bool isLanding =
            player.getVelocity().y >= 0 &&
            feetBottom >= platformTop - 4.0f &&
            feetBottom <= platformTop + 10.0f &&
            isFeetOnPlatform;

        if (player.getPosition().y > 1000.f) {
            player.setPosition(100.f, 100.f);
            player.cancelVerticalVelocity();
        }

        if (isLanding) {
            player.setPositionY(platformTop - player.getGlobalBounds().height - 2.f);
            player.setOnGround(true);
            player.cancelVerticalVelocity();
            onPlatform = true;

            sf::FloatRect playerHitbox = player.getCollisionBounds();
            if (playerHitbox.intersects(platformBounds)) {
                if (playerHitbox.left < platformBounds.left) {
                    player.setPosition(platformBounds.left - playerHitbox.width / 2.f, player.getPosition().y);
                } else if (playerHitbox.left + playerHitbox.width > platformBounds.left + platformBounds.width) {
                    player.setPosition(platformBounds.left + platformBounds.width + playerHitbox.width / 2.f, player.getPosition().y);
                }
            }
            break;
        }

        for (auto& c : collectibles) {
            if (!c.isCollected && c.getBounds().intersects(player.getBounds())) {
                c.isCollected = true;

            std::string type = c.getType();
                if (type == "strawberry") {
                    strawberryCount++;
                    std::cout << "🍓 Moe collected a strawberry! Total: " << strawberryCount << " / " << 5 << "\n";
                } else if (type == "key") {
                    hasKey = true;
                    player.collectKey();
                    std::cout << "🔑 Moe got a key!\n";
                }
            }
        }

        for (auto& door : doors) {
            if (!door.isOpened() && door.isNear(player.getBounds()) && player.hasKey()) {
                std::cout << "🎀 Moe used her key to unlock the door!\n";
                door.open();

                //  Get top and bottom bounds of the door
                sf::FloatRect topBound = door.getBounds();
                sf::FloatRect bottomBound = topBound;
                bottomBound.top += topBound.height; // move down 1 tile (same height)

                //  Remove both parts (top and bottom) of the door from platforms
                platforms.erase(
                    std::remove_if(platforms.begin(), platforms.end(),
                        [&](const Platform& p) {
                            return p.getBounds().intersects(topBound) ||
                            p.getBounds().intersects(bottomBound);
                        }),
                platforms.end()
                );
                player.removeKey();
                hasKey = false;   
            }
        }
    }

    if (!onPlatform) {
        player.setOnGround(false);
    }

    // Update Moe's animation
    player.updateAnimation(); 

    // Update camera
    camera.setCenter(player.getPosition());
    sf::Vector2f center = player.getPosition();
    float halfWidth = camera.getSize().x / 2;
    float halfHeight = camera.getSize().y / 2;

    if (center.x - halfWidth < 0) center.x = halfWidth;
    if (center.x + halfWidth > textureSize.x) center.x = textureSize.x - halfWidth;
    if (center.y - halfHeight < 0) center.y = halfHeight;
    if (center.y + halfHeight > textureSize.y) center.y = textureSize.y - halfHeight;

    camera.setCenter(center);
}


void Game_State::render(sf::RenderTarget& target) {
    target.setView(camera);
    target.draw(background);

    for (auto& tile : backgroundTiles) {
        tile.draw(target);
    }

    for (auto& platform : platforms) {
        platform.draw(target);
    }

    for (auto& door : doors) {
        if (!door.isOpened()) {
        door.draw(target);
        }
    }

    for (auto& c : collectibles) {
        if (!c.isCollected)
            c.draw(target);
    }
    
    player.draw(target);
}



int Game_State::get_next_state() {
    if (strawberryCount >= 5) {
        return WINNING_STATE;
    }
    return GAME_STATE;
}