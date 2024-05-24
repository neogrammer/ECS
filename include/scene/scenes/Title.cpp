#include "Title.hpp"
#include "../../core/GameEngine.hpp"
#include "../ECS/system/systems/RenderSystem.hpp"
#include "../ECS/system/systems/MovementSystem.hpp"
#include "../ECS/system/systems/InputSystem.hpp"
#include "../ECS/system/systems/CollisionSystem.hpp"

Title::Title(GameEngine& l_game)
	: Scene(l_game)
	, m_systems{}
{
	m_systems.clear();
	// 0 - Movement System
	m_systems.emplace_back(std::make_unique<RenderSystem>(game, &game.wnd));
	m_systems.emplace_back(std::make_unique<MovementSystem>(game));
	m_systems.emplace_back(std::make_unique<InputSystem>(game));
	m_systems.emplace_back(std::make_unique<CollisionSystem>(game));
}

Title::~Title()
{
}

void Title::propogateInput(std::vector<sf::Event>& l_evts)
{
}

void Title::processEvents(std::vector<sf::Event>& l_evts)
{
}

void Title::update(double l_dt)
{
	for (auto& s : m_systems)
	{

		if (dynamic_cast<RenderSystem*>(s.get()) == nullptr)
			s->update(l_dt);
	}
}

void Title::render(sf::RenderWindow& l_wnd)
{
	// this system only renders, which is handled outside of the traditional update section
	//  hence the odd name here that is misleading, it renders to the window, not updates
	m_systems.at(0)->update(::GameProperties::FPS);
}
