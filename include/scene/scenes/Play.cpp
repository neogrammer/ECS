#include "Play.hpp"
#include "../../core/GameEngine.hpp"
#include "../ECS/system/systems/RenderSystem.hpp"
#include "../ECS/system/systems/MovementSystem.hpp"
#include "../ECS/system/systems/InputSystem.hpp"
#include "../ECS/system/systems/CollisionSystem.hpp"

#include <fstream>
#include <iostream>

Play::Play(GameEngine& l_game, ActionMap<int>& l_actionMap, std::string l_playerCfgFile)
	: Scene(l_game, l_actionMap)
	, m_playerCfg(l_playerCfgFile)
	, m_systems{}
{

	eMgr().makeStartingEntities("play");

	m_player = eMgr().getEntity(size_t(0));
	m_player->cTransform->pos = Vec2(512, 283);
	m_player->cTransform->prevPos = Vec2(512, 283);
	m_player->cShape->sprite.setPosition({m_player->cTransform->pos.x,m_player->cTransform->pos.y});
	if (m_player == nullptr)
	{
		std::cout << "Player not found in the play scene's entity manager" << std::endl;
		throw std::runtime_error("shit");
	}

	m_systems.clear();
	// 0 - Movement System
	m_systems.emplace_back(std::make_unique<RenderSystem>(game, &game.wnd));
	m_systems.emplace_back(std::make_unique<InputSystem>(game));
	m_systems.emplace_back(std::make_unique<CollisionSystem>(game));
	m_systems.emplace_back(std::make_unique<MovementSystem>(game));

	// action bindings
	this->bind((int)Config::Inputs::Up, [this](const sf::Event&) {

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

Play::~Play()
{
}

void Play::processInput()
{
	ActionTarget<int>::processEvents();
}


void Play::processEvents(std::vector<sf::Event>& l_evts)
{
}

void Play::update(double l_dt)
{

	for (auto& s : m_systems)
	{

		if (dynamic_cast<RenderSystem*>(s.get()) == nullptr)
			s->update(l_dt);
	}
}

void Play::render(sf::RenderWindow& l_wnd)
{
	// this system only renders, which is handled outside of the traditional update section
	//  hence the odd name here that is misleading, it renders to the window, not updates
	m_systems.at(0)->update(::GameProperties::FPS);
}

std::shared_ptr<Entity> Play::player()
{
	return m_entityMgr.getEntity((size_t)0);
}
