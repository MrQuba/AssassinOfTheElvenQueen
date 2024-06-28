#include <SFML/Graphics.hpp>
#include "src/Game/Window.hpp"
#include "src/Constants/SizeConstants.hpp"
#include "src/Constants/Paths.hpp"
#include "src/Characters/Entity.hpp"
#include "src/Characters/Player.hpp"
#include "src/Types/Types.hpp"
#include "src/Logging/Logger.hpp"

int main() {
    Log("Creating Window object...");
    game::Window* window = new game::Window(sf::Vector2u(SIZE::WindowWidth, SIZE::WindowHeight));
    Log("Creating Player object...");
    Player* player = new Player(PATH::playerSprite, Area(0, 0, 32, 32));
    Log("Creating Event object...");
    sf::Event* event = new sf::Event();
    Log("Entering Game Loop...");
    while (window->isOpen()) {
        ///////////////////////////////////////////////////
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        // PRE CLEAR
        ///////////////////////////////////////////////////
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        window->getWindow().clear(sf::Color::Blue);
        ///////////////////////////////////////////////////
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        // PRE DRAW
        ///////////////////////////////////////////////////
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        while (window->getWindow().pollEvent(*event)) {
            if (event->type == sf::Event::Closed) window->getWindow().close();
        }
        player->update();

        player->draw(window->getWindow());
        ///////////////////////////////////////////////////
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        // POST DRAW
        ///////////////////////////////////////////////////
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        window->getWindow().display();
        ///////////////////////////////////////////////////
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        // POST DISPLAY
        ///////////////////////////////////////////////////
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    }
    Log("Quitting Game Loop...");
    ///////////////////////////////////////////////////
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    //Deleting objects at finished program
    ///////////////////////////////////////////////////
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    Log("Deleting Player object...");
    delete player;
    Log("Deleting Event object...");
    delete event;
    Log("Deleting Window object...");
    delete window;
    ///////////////////////////////////////////////////
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    Log("Qutting program...");
    return EXIT_SUCCESS;
}