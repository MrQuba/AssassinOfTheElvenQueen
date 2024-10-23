#include <SFML/Graphics.hpp>
#include "../Types/Types.hpp"
#pragma once
namespace Config {
	const Key bDOWN = sf::Keyboard::S;
	const Key bLEFT = sf::Keyboard::A;
	const Key bRIGHT = sf::Keyboard::D;
	const Key bJUMP = sf::Keyboard::Space;
	const Key bDASH = sf::Keyboard::LShift;
	const Key bATTACK = sf::Keyboard::E;
	class DataStructure {
	public:
		 DataStructure() {
			DOWN = bDOWN;
			LEFT = bLEFT;
			RIGHT = bRIGHT;
			JUMP = bJUMP;
			DASH = bDASH;
			ATTACK = bATTACK;
		}
		// TODO, add a initializer for custom config
		mutable Key DOWN;
		mutable Key LEFT;
		mutable Key RIGHT;
		mutable Key JUMP;
		mutable Key DASH;
		mutable Key ATTACK;
	};
}
