#include "PlayState.hpp"
#include "../../core/Game.hpp"
#include "../../gameObj/actors/player/PlayerInput.hpp"

#include "../../gameObj/actors/Player.hpp"
#include "../../core/Input.hpp"
#include "../GameState.hpp"

#include <fstream>
#include <iostream>

PlayState::PlayState(Game& l_game, ActionMap<int>& l_actionMap)
	: GameState(l_game, l_actionMap)
	, player{}
{
	// action bindings
	this->bind((int)Config::Inputs::Up, [this](const sf::Event&) {
		std::cout << "Pressed up seen by the state" << std::endl;
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

PlayState::~PlayState()
{
}

void PlayState::init()
{
	//	the_player = std::make_shared<Player>(eMgr().makeStartingEntities("play"));
	//the_player->setCurrState(PlayerInput::JUMP);

	//tmap = std::shared_ptr<Tilemap>(new Tilemap{ eMgr(), "intro" });
}



void PlayState::processInput()
{
	ActionTarget<int>::processEvents();
	player.processInput();
}


void PlayState::processEvents(std::vector<sf::Event>& l_evts)
{
}

void PlayState::update(double l_dt)
{
	 player.update(sf::seconds((float)l_dt));
}


void PlayState::render(sf::RenderWindow& l_wnd)
{
	//tmap->draw(l_wnd);
	player.render(l_wnd);
}
