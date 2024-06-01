#ifndef INPUT_HPP__
#define INPUT_HPP__

#include <SFML/System/Time.hpp>
#include "../gameObj/actors/player/PlayerInput.hpp"

class Input
{
	PlayerInput m_inputType;
public:
	Input();
	Input(PlayerInput l_type);
	~Input();
	Input(const Input&) = default;
	Input& operator=(const Input&) = default;
	Input(Input&&) = default;
	Input& operator=(Input&&) = default;

	void update(sf::Time l_dt);
	PlayerInput id();
};

#endif