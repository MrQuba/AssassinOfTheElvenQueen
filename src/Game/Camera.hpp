#include <SFML/Graphics.hpp>
#include "../Types/Types.hpp"
#include "../Logging/Logger.hpp"
#pragma once

class Camera {
public:
    Camera(const Point center, const Size size)
        : view(center, size) {}
    
    void update(const sf::Sprite& sprite) {
        Position center = Position(sprite.getPosition().x + (sprite.getGlobalBounds().width / 2), center.y = 500);
        if (center.x < 957) center.x = 957;
        else if (center.x > 3500) center.x = 3500;
        view.setCenter(center);
    }
    
    sf::View& getView() {
        return view;
    }

private:
    sf::View view;
};
