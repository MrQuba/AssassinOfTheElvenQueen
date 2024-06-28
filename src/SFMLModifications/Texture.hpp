#include <SFML/Graphics.hpp>
#include "../Types/Types.hpp"
#pragma once

class Texture : public sf::Texture{
public:
	/// <summary>
	/// Constructor, a shortcut for texture.loadFromFile...
	/// throws "Error loading texture" if it fails
	/// </summary>
	/// <param name="path">Path to the file</param>
	/// <param name="area">Area of the texture</param>
	Texture(Path path, Area area){
		if (!this->loadFromFile(path, area)) throw ("Error loading texture");
	}
	/// <summary>
	/// 
	/// </summary>
	/// <returns>pointer to sf::Texture</returns>
	sf::Texture* getTexture() {
		return this;
	}
};