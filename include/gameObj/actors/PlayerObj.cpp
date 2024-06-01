#include "PlayerObj.hpp"
#include <iostream>

PlayerObj::PlayerObj()
	: ActorObj(Config::textures.get((int)Config::Textures::Player), sf::IntRect(0,0,84,84),Vec2(84.f,84.f),Vec2(316.f,242.f))
	, ActionTarget<int>(Config::inputs)
{

	// action bindings
	this->bind((int)Config::Inputs::Up, [this](const sf::Event&) {
		std::cout << "Pressed up seen by the player object" << std::endl;

		});
	this->bind((int)Config::Inputs::Down, [this](const sf::Event&) {
		});
	this->bind((int)Config::Inputs::Left, [this](const sf::Event&) {
		
		});

	this->bind((int)Config::Inputs::Right, [this](const sf::Event&) {
		
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
	ActionTarget<int>::processEvents();
}

void PlayerObj::update(sf::Time l_dt)
{
}

void PlayerObj::render(sf::RenderWindow& l_wnd)
{
	l_wnd.draw(this->spr());
}
