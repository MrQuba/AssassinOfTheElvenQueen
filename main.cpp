#include <SFML/Graphics.hpp>
#include <vector>
#include "src/Game/Window.hpp"
#include "src/Constants/SizeConstants.hpp"
#include "src/Constants/Paths.hpp"
#include "src/Characters/Entity.hpp"
#include "src/Characters/Player.hpp"
#include "src/Characters/Queen.hpp"
#include "src/Enviroment/Enviroment.hpp"
#include "src/Types/Types.hpp"
#include "src/Logging/Logger.hpp"

int main() {
    Log("Creating Window object...");
    std::vector<Drawable*> ENTITIES;
    std::vector<Entity*> COLLISIONS;
    std::vector<Enviroment*> ENVIROMENT;
    game::Window* window = new game::Window(sf::Vector2u(SIZE::WindowWidth, SIZE::WindowHeight), "Assassin of the Elven Queen", 60, WindowStyle(sf::Style::Fullscreen));
    Log("Creating Player object...");
    Player* player = new Player(PATH::playerSprite, Area(0, 0, 32, 32), Position(90, SIZE::WindowHeight - 90));
    Log("Creating Event object...");
    Queen* queen = new Queen(PATH::playerSprite, Area(0, 0, 32, 32));
    Enviroment* ground = new Enviroment(PATH::playerSprite, 
        Area(0, 0, 32, 32), 
        Size(SIZE::WindowWidth, 80), 
        (Type)TYPE::GROUND, 
        Position(0, window->getWindow().getSize().y - 80));
    Enviroment* roof = new Enviroment(PATH::playerSprite, 
        Area(0, 0, 32, 32), 
        Size(SIZE::WindowWidth, 80), (Type)TYPE::ROOF, 
        Position(0, 0));
    Enviroment* wall_left = new Enviroment(PATH::playerSprite,
        Area(0, 0, 32, 32),
        Size(80, SIZE::WindowHeight - 160), (Type)TYPE::WALL,
        Position(0, 80));
    Enviroment* wall_right = new Enviroment(PATH::playerSprite,
        Area(0, 0, 32, 32),
        Size(80, SIZE::WindowHeight - 160), (Type)TYPE::WALL,
        Position(SIZE::WindowWidth-80, 80));
    ENVIROMENT.push_back(ground);
    ENVIROMENT.push_back(roof);
    ENVIROMENT.push_back(wall_left);
    ENVIROMENT.push_back(wall_right);
    ENTITIES.push_back(ground);
    ENTITIES.push_back(roof);
    ENTITIES.push_back(wall_left);
    ENTITIES.push_back(wall_right);
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
        // PRE DRAW
        ///////////////////////////////////////////////////
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        while (window->getWindow().pollEvent(*event)) {
            if (event->type == sf::Event::Closed) window->getWindow().close();
            if (event->type == sf::Event::KeyPressed) if(event->key.code == sf::Keyboard::Escape) window->getWindow().close();
        }
        for (auto& env : ENVIROMENT) {
            env->update();
            env->draw(window->getWindow());
        }
        for (auto& ent : ENTITIES) {
            ent->update();
            ent->draw(window->getWindow());
        }
        for (auto& ent : COLLISIONS) {
            for (auto& ent2 : COLLISIONS)
                if (ent != ent2)
                    ent->onCollision(ent2);
            for (auto& env : ENVIROMENT) {
                ent->onCollisionWithGround(env);
            }
        }
        window->getWindow().setView(*player->getView());
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
    Log("Deleting Roof object...");
    delete roof;
    Log("Deleting Ground object...");
    delete ground;
    Log("Deleting Left Wall object...");
    delete wall_left;
    Log("Deleting Right Wall object...");
    delete wall_right;
    Log("Deleting Event object...");
    delete event;
    Log("Deleting Window object...");
    delete window;
    ///////////////////////////////////////////////////
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    Log("Qutting program...");
    return EXIT_SUCCESS;
}