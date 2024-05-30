#ifndef PLAYERSTATE_HPP__
#define PLAYERSTATE_HPP__
#include "Player.hpp"
#include "Input.hpp"
#include <string>
class PlayerState
{
public:
	const std::string id;
	PlayerState(const std::string& l_id);
	virtual ~PlayerState();
	virtual void handleInput(Player& player, Input input) = 0;
	virtual void update(Player& player, sf::Time l_dt);
};

#endif