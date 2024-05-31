#ifndef SCENE_HPP__
#define SCENE_HPP__
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
#include <map>
#include "../ECS/EntityManager.hpp"
#include "../action/ActionTarget.hpp"
#include "../core/Config.hpp"
#include "../ECS/system/System.hpp"
class Game;

class GameState : public ActionTarget<int>
{

protected:
	Game& game;
	EntityManager m_entityMgr{};
	bool m_paused{ false };
	bool m_hasEnded{ false };



public:
	GameState(Game& l_game, ActionMap<int>& l_actionMap);

	std::shared_ptr<System> currentSystem;

	virtual ~GameState();

	virtual void init() = 0;
	virtual void processInput() = 0;
	virtual void processEvents(std::vector<sf::Event>& l_evts) = 0;
	virtual void update(double l_dt) = 0;
	virtual void render(sf::RenderWindow& l_wnd) = 0;


	EntityManager& eMgr();
};

#endif