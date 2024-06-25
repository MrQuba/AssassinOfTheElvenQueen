#include <SFML/Graphics.hpp>
#include "src/Game/Window.hpp"
#include "src/Constants/SizeConstants.hpp"
#include "src/Constants/Paths.hpp"
#include "src/Characters/Entity.hpp"
#include "src/Characters/Player.hpp"
#include "src/Types/Types.hpp"


int main() {
    game::Window* window = new game::Window(sf::Vector2u(SIZE::WindowWidth, SIZE::WindowHeight));
    Player* player = new Player(PATH::playerSprite, Area(0, 0, 32, 32));
    sf::Event* event = new sf::Event();
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
    ///////////////////////////////////////////////////
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    //Deleting objects at finished program
    ///////////////////////////////////////////////////
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    delete player;
    delete event;
    delete window;
    ///////////////////////////////////////////////////
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return EXIT_SUCCESS;
}