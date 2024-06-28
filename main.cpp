#include <SFML/Graphics.hpp>
#include <vector>
#include "src/Game/Window.hpp"
#include "src/Constants/SizeConstants.hpp"
#include "src/Constants/Paths.hpp"
#include "src/Characters/Entity.hpp"
#include "src/Characters/Player.hpp"
#include "src/Characters/Queen.hpp"
#include "src/Enviroment/Ground.hpp"
#include "src/Types/Types.hpp"
#include "src/Logging/Logger.hpp"

int main() {
    Log("Creating Window object...");
    std::vector<Drawable*> ENTITIES;
    std::vector<Entity*> COLLISIONS;
    game::Window* window = new game::Window(sf::Vector2u(SIZE::WindowWidth, SIZE::WindowHeight), "Assassin of the Elven Queen", 60, WindowStyle(sf::Style::Fullscreen));
    Log("Creating Player object...");
    Player* player = new Player(PATH::playerSprite, Area(0, 0, 32, 32));
    Log("Creating Event object...");
    Queen* queen = new Queen(PATH::playerSprite, Area(0, 0, 32, 32));
    Ground* ground = new Ground(PATH::playerSprite, Area(0, 0, 32, 32), Size(1920, 80));
    ENTITIES.push_back(ground);
    ENTITIES.push_back(player);
    ENTITIES.push_back(queen);
    COLLISIONS.push_back(player);
    COLLISIONS.push_back(queen);
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
        // POST CLEAR
        ///////////////////////////////////////////////////
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        while (window->getWindow().pollEvent(*event)) {
            if (event->type == sf::Event::Closed) window->getWindow().close();
            if (event->type == sf::Event::KeyPressed) if(event->key.code == sf::Keyboard::Escape) window->getWindow().close();
        }

        for (auto& ent : ENTITIES) {
            ent->update();
            ent->draw(window->getWindow());
        }
        for (auto& ent : COLLISIONS) {
            for (auto& ent2 : COLLISIONS)
                if(ent != ent2)
            ent->onCollision(ent2);
            Console(ent->getSprite()->getPosition().y);
            ent->onCollisionWithGround(ground);
        }
        ///////////////////////////////////////////////////
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        // PRE DRAW
        ///////////////////////////////////////////////////
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
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
    Log("Deleting Queen object...");
    delete queen;
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