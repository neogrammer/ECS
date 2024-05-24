#ifndef GAMEENGINE_HPP__
#define GAMEENGINE_HPP__
#include <vector>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../ECS/EntityManager.hpp"
#include "../ECS/system/System.hpp"

#include <memory>
#include <utility>

struct GameProperties
{
	static constexpr double FPS = 0.016666667;
	static constexpr int SCRW = 1024;
	static constexpr int SCRH = 576;
};

class GameEngine
{

	std::shared_ptr<Entity> m_player{};
	EntityManager m_entityManager{};
	std::vector<std::unique_ptr<System> > m_systems;

	// handle the entirety of the game with these four functions
	void handleWindowEvents(std::vector<sf::Event>& l_evts);
	void propogateInput(std::vector<sf::Event>& l_evts);
	void update(double l_dt);
	void render(sf::RenderWindow& l_wnd);

public:
	sf::RenderWindow wnd;
	static bool gameRunning;
	Entity& player();
	EntityManager& eMgr();
	// cuz im an explicit mofukka
	explicit GameEngine();
	~GameEngine() = default;
	// child safety deletes.  Can't move it, cant copy it.  Cuz it's the fucking game, doi.  
	GameEngine(const GameEngine&) = delete;
	GameEngine& operator=(const GameEngine&) = delete;
	GameEngine(GameEngine&&) = delete;
	GameEngine& operator=(GameEngine&&) = delete;

	//  One function to rule them all
	void mainLoop();



};

#endif