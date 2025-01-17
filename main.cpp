#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>
#include "src/Game/Window.hpp"
#include "src/Constants/SizeConstants.hpp"
#include "src/Constants/Paths.hpp"
#include "src/Characters/Entity.hpp"
#include "src/Characters/Player.hpp"
#include "src/Characters/Queen/Queen.hpp"
#include "src/Enviroment/Enviroment.hpp"
#include "src/Types/Types.hpp"
enum Scenes{
    Menu = 0,
    Game = 1,
    Finish = 2
};
// TODO, clean code
int main() {
	short scene = Menu;
    std::vector<Drawable*> ENTITIES;
    std::vector<Entity*> COLLISIONS;
    std::vector<Enviroment*> ENVIROMENT;
    game::Window* window = new game::Window(sf::Vector2u(SIZE::WindowWidth, SIZE::WindowHeight), "Assassin of the Elven Queen", 60, WindowStyle(sf::Style::Fullscreen));
    Player<Queen>* player = new Player<Queen>(PATH::playerTexture, Area(0, 0, 32, 32), Position(SIZE::GroundHeight, SIZE::WindowHeight - SIZE::GroundHeight -32), &(window->getWindow()));
    Queen* queen = new Queen(PATH::playerTexture, Area(0, 0, 32, 32), player,  Position(std::trunc((SIZE::GroundHeight*SIZE::GroundHeight)/4.f), SIZE::WindowHeight - SIZE::GroundHeight -32));
    queen->setColor(sf::Color::Magenta);
    Enviroment* ground = new Enviroment(PATH::enviromentTexture,
        Area(0, 0, 32, 32), 
        Size(SIZE::WorldWidth, SIZE::GroundHeight),
        (Type)TYPE::GROUND, 
        Position(0, SIZE::WorldHeight-SIZE::GroundHeight));
    ground->setFillColor(sf::Color::Black);
    Enviroment* roof = new Enviroment(PATH::enviromentTexture,
        Area(0, 0, 32, 32), 
        Size(SIZE::WorldWidth, SIZE::GroundHeight), (Type)TYPE::ROOF,
        Position(0, -(int)SIZE::GroundHeight + 1));
    roof->setFillColor(sf::Color::Black);
    Enviroment* wall_left = new Enviroment(PATH::enviromentTexture,
        Area(0, 0, 32, 32),
        Size(10, SIZE::WindowHeight + (SIZE::GroundHeight)), (Type)TYPE::WALL,
        Position(-10, -(int)SIZE::GroundHeight));
    wall_left->setFillColor(sf::Color::Black);
    Enviroment* wall_right = new Enviroment(PATH::enviromentTexture,
        Area(0, 0, 32, 32),
        Size(10, SIZE::WindowHeight + (SIZE::GroundHeight)), (Type)TYPE::WALL,
        Position(SIZE::WorldWidth, -(int)SIZE::GroundHeight));
    wall_right->setFillColor(sf::Color::Black);
    Enviroment* background = new Enviroment(PATH::backgroundTexture,
        Area(0, 0, SIZE::WorldWidth, SIZE::WorldHeight),
        Size(SIZE::WorldWidth, SIZE::WorldHeight), (Type)TYPE::BACKGROUNDWALL,
        Position(0,0));
    player->boss_ptr = queen;
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
    while (window->isOpen()) {
        window->getWindow().clear(sf::Color::White);
        while (window->getWindow().pollEvent(*event)) {
            if (event->type == sf::Event::Closed) window->getWindow().close();
            if (event->type == sf::Event::KeyPressed) if(event->key.code == sf::Keyboard::Escape) window->getWindow().close();
        }
	switch(scene){
		case Menu:
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) scene = Game;
			break;
		case Game: 
			background->draw(window->getWindow());
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
            if(player->current_Health <= 0) scene = Finish;
            if(queen->current_Health <= 0) scene = Finish;
			break;
		case Finish: 
            window->getWindow().close();
            if(player->current_Health <= 0) std::cout << "You loose" << std::endl;
            else if(queen->current_Health <= 0) std::cout << "You win" << std::endl;
			break;
	}
        window->getWindow().display();
    }
    delete queen;
    delete player;
    delete roof;
    delete ground;
    delete wall_left;
    delete wall_right;
    delete background;
    delete event;
    delete window;
    return EXIT_SUCCESS;
}
