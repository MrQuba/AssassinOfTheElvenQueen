#include "Window.hpp"
game::Window::Window(sf::Vector2u size, Title title, Framerate fps, WindowStyle style)
{
	window.create(sf::VideoMode(size.x, size.y), title, style);
	//window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(fps);

}

bool game::Window::isOpen()
{
	return window.isOpen();
}

sf::RenderWindow& game::Window::getWindow()
{
	return this->window;
}

game::Window::~Window()
{
	window.close();
}
