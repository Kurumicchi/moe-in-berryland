#include "Menu_State.h"
#include <string>
#include <stdexcept>
#include <iostream>

using namespace sf;

Menu_State::Menu_State()
    : play{false}
{
    if (!bgTexture.loadFromFile("assets/Import/Moemenu.png")) {
        std::cerr << "Failed to load menu background image\n";
    }
    background.setTexture(bgTexture);
    background.setScale(
        static_cast<float>(screen_width) / bgTexture.getSize().x,
        static_cast<float>(screen_height) / bgTexture.getSize().y
    );
}

void Menu_State::handle_event(const sf::Event& event)
{
    if (event.type == Event::KeyPressed) {
        if (event.key.code == Keyboard::Z) {
            play = true;
        }
    }
}

void Menu_State::update()
{
    // No update logic needed for the menu state
}

void Menu_State::render(RenderTarget & target)
{
    target.draw(background);
}

int Menu_State::get_next_state()
{
    if (play) {
        play = false;
        return GAME_STATE;
    } else {
        return MENU_STATE;
    }
}