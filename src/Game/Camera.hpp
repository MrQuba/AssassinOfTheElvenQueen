#include <SFML/Graphics.hpp>
#include "../Types/Types.hpp"
#include "../Logging/Logger.hpp"
#pragma once

class Camera {
public:
    Camera(const Point center, const Size size)
        : view(center, size) {}
    
    void update(const sf::Sprite& sprite) {
        view.setCenter(static_cast<int>(sprite.getPosition().x + (sprite.getGlobalBounds().width / 2)), static_cast<int>(0.75f * sprite.getPosition().y ));
    }
    
    sf::View& getView() {
        return view;
    }

private:
    sf::View view;
};
