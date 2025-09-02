#include "Game.h"

#include "Menu_State.h"
#include "Game_State.h"
#include "Winning_State.h"

using namespace sf;

Game::Game(std::string const & title,
           unsigned width,
           unsigned height)
    : window{VideoMode{width, height},
              title,
              Style::Titlebar | Style::Close},
      current_state(MENU_STATE),
      running(true)
{
    // Insert all states you want in your game
    states.insert({MENU_STATE, std::make_unique<Menu_State>()});
    states.insert({GAME_STATE, std::make_unique<Game_State>()});
    states.insert({WINNING_STATE, std::make_unique<Winning_State>()});
}


void Game::start()
{
    clock.restart();

    while (running)
    {
        // Handle events first
        handle_events();

        // Update current state
        states.at(current_state)->update();

        // Clear
        window.clear();

        // Let the state render itself
        states.at(current_state)->render(window);

        // Display rendered frame
        window.display();

        // Change state if needed
        int next = states.at(current_state)->get_next_state();
        if (next != current_state) {
            if (states.find(next) == states.end()) {
                // If state doesn't exist, create it
                switch (next) {
                    case MENU_STATE:
                        states[next] = std::make_unique<Menu_State>();
                        break;
                    case GAME_STATE:
                        states[next] = std::make_unique<Game_State>();
                        break;
                    case WINNING_STATE:
                        states[next] = std::make_unique<Winning_State>();
                        break;
                    default:
                        break;
                }
            }
            current_state = next;
        }

        // Frame rate control
        delay(1000.0f / fps);
    }
}

void Game::handle_events()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            running = false;

        states.at(current_state)->handle_event(event);
    }
}

void Game::delay(float frameTime)
{
    sf::Time elapsed = clock.getElapsedTime();
    sf::Int32 delay = static_cast<sf::Int32>(frameTime - elapsed.asMilliseconds());

    if (delay > 0)
        sf::sleep(sf::milliseconds(delay));

    clock.restart();
}