#ifndef PLAYER_HPP__
#define PLAYER_HPP__
#include <SFML/Graphics/RenderWindow.hpp>
#include "player/PlayerInput.hpp"


#include <stack>
#include <memory>
#include <utility>

class PlayerState;
class Input;
class Player
{

	
	std::vector<std::shared_ptr<Input> > m_inputVec;

	std::unique_ptr<PlayerState> m_currentState;
	bool m_facingLeft{ false };
	bool m_canJump{ false };
	PlayerState* oldState;

public:
	Player();
	~Player();
	
	void handleInput();
	void update(sf::Time l_dt);
	void render(sf::RenderWindow& l_wnd);

	void pushInput(std::shared_ptr<Input> l_input);

	bool facingLeft() const;
	void setFacingLeft(bool l_facingLeft);
	bool canJump() const;
	void setCanJump(bool l_canJump);
	void setCurrState(PlayerInput l_newState);
};

#endif