#include "Play.hpp"
#include "../../core/GameEngine.hpp"
#include "../../ECS/system/systems/RenderSystem.hpp"
#include "../../ECS/system/systems/MovementSystem.hpp"
#include "../../ECS/system/systems/InputSystem.hpp"
#include "../../ECS/system/systems/CollisionSystem.hpp"
#include "../../player/PlayerInput.hpp"

#include "../../player/Player.hpp"
#include "../../player/Input.hpp"


#include <fstream>
#include <iostream>

Play::Play(GameEngine& l_game, ActionMap<int>& l_actionMap, std::string l_playerCfgFile)
	: Scene(l_game, l_actionMap), the_player{}
	, m_playerCfg(l_playerCfgFile)
	, renderSystem{ nullptr }
	, inputSystem{ nullptr }
	, collisionSystem{ nullptr }
	, movementSystem{ nullptr }
	, tmap{}
{
	
	inputSystem = std::make_shared<InputSystem>(game);
	renderSystem = std::make_shared<RenderSystem>(game, &game.wnd);
	movementSystem = std::make_shared<MovementSystem>(game);
	collisionSystem = std::make_shared<CollisionSystem>(game);
	


	// action bindings
	this->bind((int)Config::Inputs::Up, [this](const sf::Event&) {
		inputSystem->currentlyPressed[0].second = true;
		the_player->pushInput(std::make_shared<Input>(PlayerInput::JUMP));

		});
	this->bind((int)Config::Inputs::Down, [this](const sf::Event&) {
		inputSystem->currentlyPressed[1].second = true;

		});
	this->bind((int)Config::Inputs::Left, [this](const sf::Event&) {
		inputSystem->currentlyPressed[2].second = true;
		the_player->pushInput(std::make_shared<Input>(PlayerInput::MOVE_LEFT));

		});

	this->bind((int)Config::Inputs::Right, [this](const sf::Event&) {
		inputSystem->currentlyPressed[3].second = true;
		the_player->pushInput(std::make_shared<Input>(PlayerInput::MOVE_RIGHT));

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

Play::~Play()
{
}

void Play::init()
{
	the_player = std::make_shared<Player>(eMgr().makeStartingEntities("play"));
	the_player->setCurrState(PlayerInput::JUMP);
	currentSystem = inputSystem;

	tmap = std::shared_ptr<Tilemap>(new Tilemap{ eMgr(), "intro" });
}



void Play::processInput()
{
	ActionTarget<int>::processEvents();
	if(inputSystem->inputMap[InputSystem::Signal::Left] == InputSystem::Status::Off
		&& inputSystem->inputMap[InputSystem::Signal::Right] == InputSystem::Status::Off)
		the_player->pushInput(std::make_shared<Input>(PlayerInput::NONE));
	the_player->handleInput();
}


void Play::processEvents(std::vector<sf::Event>& l_evts)
{
}

void Play::update(double l_dt)
{
	collisionSystem->update(l_dt);

	movementSystem->update(l_dt);

	the_player->update(sf::seconds((float)l_dt));
}


void Play::render(sf::RenderWindow& l_wnd)
{
	tmap->draw(l_wnd);
	the_player->render(l_wnd);


}

std::shared_ptr<Entity> Play::player()
{
	return m_entityMgr.getEntity((size_t)0);
}