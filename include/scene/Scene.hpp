#ifndef SCENE_HPP__
#define SCENE_HPP__
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
#include "../ECS/EntityManager.hpp"

class GameEngine;

class Scene
{
protected:
	GameEngine& game;
	EntityManager m_entityMgr{};
	bool m_paused{ false };
	bool m_hasEnded{ false };

	

public:
	Scene(GameEngine& l_game);

	virtual ~Scene();


	virtual void propogateInput(std::vector<sf::Event> l_evts) = 0;
	virtual void processEvents(std::vector<sf::Event>& l_evts) = 0;
	virtual void update(double l_dt) = 0;
	virtual void render(sf::RenderWindow& l_wnd) = 0;


	EntityManager& eMgr();
};

#endif
