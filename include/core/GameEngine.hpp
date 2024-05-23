#ifndef GAMEENGINE_HPP__
#define GAMEENGINE_HPP__
#include <vector>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class GameEngine
{
public:
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

	// handle the entirety of the game with these four functions
	void handleWindowEvents(std::vector<sf::Event>& l_evts);
	void propogateInput(std::vector<sf::Event>& l_evts);
	void update(double l_dt);
	void render(sf::RenderWindow& l_wnd);

};

#endif