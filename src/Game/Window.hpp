#include <SFML/Graphics.hpp>
#include "../Types/Types.hpp"
#pragma once
namespace game {
	class Window {
		public:
			/// <summary>
			/// Constructor for window
			/// </summary>
			/// <param name="size">default 600 by 800 pixels</param>
			/// <param name="title">default "Window"</param>
			/// <param name="fps">default 60</param>
			/// <param name="style">default sf::Style::Default</param>
			Window(sf::Vector2u size = sf::Vector2u(600, 800), Title title = "Window", Framerate fps = 60, WindowStyle style = sf::Style::Default);
		bool isOpen();
		sf::RenderWindow& getWindow();
		~Window();
	private:
		sf::RenderWindow window;
	};
}
