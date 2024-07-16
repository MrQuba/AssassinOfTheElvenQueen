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
    Player* player = new Player(PATH::playerTexture, Area(0, 0, 32, 32), Position(90, SIZE::WindowHeight - 90));
    player->setColor(sf::Color::Red);
    Log("Creating Event object...");
    Queen* queen = new Queen(PATH::playerTexture, Area(0, 0, 32, 32));
    Enviroment* ground = new Enviroment(PATH::enviromentTexture,
        Area(0, 0, 32, 32), 
        Size(SIZE::WorldWidth, SIZE::GroundHeight),
        (Type)TYPE::GROUND, 
        Position(0, SIZE::WorldHeight-SIZE::GroundHeight));
    Enviroment* roof = new Enviroment(PATH::enviromentTexture,
        Area(0, 0, 32, 32), 
        Size(SIZE::WorldWidth, SIZE::GroundHeight), (Type)TYPE::ROOF,
        Position(0, -(int)SIZE::GroundHeight + 1));
    Enviroment* wall_left = new Enviroment(PATH::enviromentTexture,
        Area(0, 0, 32, 32),
        Size(10, SIZE::WindowHeight + (SIZE::GroundHeight)), (Type)TYPE::WALL,
        Position(-10, -(int)SIZE::GroundHeight));
    Enviroment* wall_right = new Enviroment(PATH::enviromentTexture,
        Area(0, 0, 32, 32),
        Size(10, SIZE::WindowHeight + (SIZE::GroundHeight)), (Type)TYPE::WALL,
        Position(SIZE::WorldWidth, -(int)SIZE::GroundHeight));
    Enviroment* background = new Enviroment(PATH::backgroundTexture,
        Area(0, 0, SIZE::WorldWidth, SIZE::WorldHeight),
        Size(SIZE::WorldWidth, SIZE::WorldHeight), (Type)TYPE::BACKGROUNDWALL,
        Position(0,0));
    ENVIROMENT.push_back(background);
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
        window->getWindow().clear(sf::Color::White);
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
    Log("Deleting Background Wall object...");
    delete background;
    Log("Deleting Event object...");
    delete event;
    Log("Deleting Window object...");
    delete window;
    ///////////////////////////////////////////////////
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    Log("Qutting program...");
    return EXIT_SUCCESS;
}
