#include "PlayerObj.hpp"
#include <iostream>

PlayerObj::PlayerObj()
	: ActorObj(Config::textures.get((int)Config::Textures::Player), sf::IntRect(0,0,84,84),Vec2(84.f,84.f),Vec2(316.f,242.f))
	, ActionTarget<int>(Config::inputs)
{
	getVelocity().y = 100.f;


	// action bindings
	this->bind((int)Config::Inputs::Up, [this](const sf::Event&) {
		//std::cout << "Pressed up seen by the player object" << std::endl;
		upPressed = true;

		});
	this->bind((int)Config::Inputs::Down, [this](const sf::Event&) {
		downPressed = true;
		});
	this->bind((int)Config::Inputs::Left, [this](const sf::Event&) {
		leftPressed = true;
		m_isFacingLeft = true;
		getVelocity().x = -100.0f;
		});

	this->bind((int)Config::Inputs::Right, [this](const sf::Event&) {
		getVelocity().x = 100.0f;
		rightPressed = true;
		m_isFacingLeft = false;
		});

	this->bind((int)Config::Inputs::A, [this](const sf::Event&) {
		});
	this->bind((int)Config::Inputs::AxisX, [this](const sf::Event&) {
		sf::Joystick::update();

		float speed = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);
		if (speed < 0.0f)
		{

		}
		else
		{

		}

		});
	this->bind((int)Config::Inputs::DPadX, [this](const sf::Event&) {
		sf::Joystick::update();

		float speed = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX);
		if (speed < 0.0f)
		{

		}
		else
		{

		}

		});

}

PlayerObj::~PlayerObj()
{
}

void PlayerObj::processInput()
{
	m_hasCollidedWithGround = false;
	downPressed = false;
	leftPressed = false;
	rightPressed = false;
	upPressed = false;

	ActionTarget<int>::processEvents();
}

void PlayerObj::update(sf::Time l_dt)
{
	if (upPressed)
	{
		if (m_canJump)
		{
			this->getVelocity().y = -1.f * 180.f;
			m_canJump = false;
			this->collidedWithGround() = false;
			this->m_isJumping = true;
			
		}
	}

	if (this->m_isJumping || this->m_isFalling)
	{
		getVelocity().y += 60.f * l_dt.asSeconds();

		if (getVelocity().y <= 0.f)
		{
			this->m_isJumping = true;
		}
		else if (getVelocity().y > 0.f)
		{
			this->m_isJumping = false;
			this->m_isFalling = true;
		}
		if (this->m_isFalling && m_hasCollidedWithGround == true)
		{
			m_isFalling = false;
			getVelocity().y -= getVelocity().y * 2;
		}
	}

	if (!leftPressed && !rightPressed)
	{
		getVelocity().x *= 0.05f;
		if (abs(getVelocity().x) < 0.1f)
			getVelocity().x = 0.f;
	}
	if (m_hasCollidedWithGround == true)
	{
		getVelocity().y = 0.f;
		m_canJump = true;
	}
	else
	{
		m_canJump = false;

		
	}


this->spr().move(this->getVelocity().x * l_dt.asSeconds(), this->getVelocity().y * l_dt.asSeconds());
}

void PlayerObj::render(sf::RenderWindow& l_wnd)
{
	l_wnd.draw(this->spr());
}

bool& PlayerObj::collidedWithGround()
{
	return m_hasCollidedWithGround;
}

bool& PlayerObj::canJump()
{
	return m_canJump;
}

bool& PlayerObj::facingLeft()
{
	return m_isFacingLeft;
}
