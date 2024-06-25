#include "Component.hpp"
#include "..\Types\Types.hpp"
#include <SFML/Graphics.hpp>
#pragma once
class HealthComponent : public Component, sf::RectangleShape {
public:
	HealthComponent(Size size) : RectangleShape(size), background(size) {
		this->setFillColor(sf::Color::Red);
		background.setFillColor(sf::Color::Black);
	}
	void update() override {
		//if (health_Pointer = nullptr) 
			//throw ("health_Pointer is nullptr, create reference to health varaible using createReference(Health* var)");
		if (*health_Pointer < 0) *health_Pointer = 0;
		this->setSize(Size(*health_Pointer, 16.f));
	}
	void createReference(Health* var) {
		health_Pointer = var;
	}
	void draw(sf::RenderWindow& window) override {
		window.draw(background);
		window.draw(static_cast<sf::RectangleShape&>(*this));
	}
	~HealthComponent() {
		delete health_Pointer;
	}
private:
	sf::RectangleShape background;
	Health* health_Pointer = nullptr;
};