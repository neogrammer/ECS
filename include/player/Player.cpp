#include "Player.hpp"
#include "../ECS/Entity.hpp"
#include "IdleState.hpp"
#include "RunningState.hpp"
#include "RunningShootingState.hpp"
#include "JumpingShootingState.hpp"
#include "JumpingState.hpp"
#include "ShootingState.hpp"
#include "Input.hpp"


Player::Player(std::shared_ptr<Entity> l_playerEnt)
	:  m_inputVec{}, m_entity{}, m_currentState{}
	, oldState{nullptr}
{
	
	m_inputVec.clear();
	m_entity = l_playerEnt;


	m_currentState = std::make_unique<JumpingState>();
	m_canJump = false;
}

Player::~Player()
{
	if (oldState)
	{
		delete oldState;
		oldState = nullptr;
	}
}

void Player::handleInput()
{
	for (auto& i : m_inputVec)
	{
		

		m_currentState->handleInput(*this, *i);

	}
	m_inputVec.clear();

}

void Player::update(sf::Time l_dt)
{
	if (oldState)
	{
		delete oldState;
		oldState = nullptr;
	}
	if (m_inputVec.empty() && m_inputVec.capacity() > 0)
	{
		m_inputVec.resize(0);
		m_inputVec.shrink_to_fit();
	}

	this->m_entity->update(l_dt);
	if (this->m_entity->getComponent<cRigidBody>().vel.y == 0.0f)
	{
		this->setCanJump(true);
	}

}

void Player::render(sf::RenderWindow& l_wnd)
{
	get().render(l_wnd);
}

void Player::pushInput(std::shared_ptr<Input> l_input)
{
	m_inputVec.push_back(l_input);
}

bool Player::facingLeft() const
{
	return m_facingLeft;
}

void Player::setFacingLeft(bool l_facingLeft)
{
	m_facingLeft = l_facingLeft;
}

Entity& Player::get()
{
	return *m_entity;
}

std::shared_ptr<Entity> Player::getPtr()
{
	return m_entity;
}

bool Player::canJump()
{
	return m_canJump;
}

void Player::setCanJump(bool l_canJump)
{
	m_canJump = l_canJump;
}

void Player::setCurrState(PlayerInput l_newState)
{
	oldState = m_currentState.release();
	m_currentState = nullptr;
	if (l_newState == PlayerInput::NONE)
	{
		m_currentState = std::make_unique<IdleState>();
	}
	else if (l_newState == PlayerInput::MOVE_LEFT)
	{
		m_currentState = std::make_unique<RunningState>();
	} 
	else if (l_newState == PlayerInput::MOVE_RIGHT)
	{
		m_currentState = std::make_unique<RunningState>();
	}
	else if (l_newState == PlayerInput::JUMP)
	{
		m_currentState = std::make_unique<JumpingState>();
	}
	else if (l_newState == PlayerInput::SHOOT)
	{
		m_currentState = std::make_unique<ShootingState>();
	}
	
}
