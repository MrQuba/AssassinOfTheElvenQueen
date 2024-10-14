#include "Queen.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

void Queen::draw(sf::RenderWindow& window) {
		window.draw(static_cast<sf::Sprite&>(*this));

    for(auto& a : projectiles) window.draw(*(a->getSprite()));
		health->setPos(Position(window.getView().getCenter().x - (window.getView().getSize().x / 2) + (displayHealth / 2),
			window.getView().getCenter().y + (window.getView().getSize().y / 2) - 16.f));
		for (Component* comp : drawableComponents) {
			comp->draw(window);
		}
  }
