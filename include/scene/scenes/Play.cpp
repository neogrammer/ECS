#include "Play.hpp"
#include "../../core/GameEngine.hpp"
#include "../ECS/system/systems/RenderSystem.hpp"
#include "../ECS/system/systems/MovementSystem.hpp"
#include "../ECS/system/systems/InputSystem.hpp"
#include "../ECS/system/systems/CollisionSystem.hpp"

#include <fstream>
#include <iostream>

Play::Play(GameEngine& l_game, std::string l_playerCfgFile)
	: Scene(l_game)
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
}

Play::~Play()
{
}

void Play::propogateInput(std::vector<sf::Event>& l_evts)
{
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
