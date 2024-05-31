#ifndef GAME_HPP__
#define GAME_HPP__
#include <vector>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../core/Config.hpp"


#include <map>
#include <memory>
#include <utility>
#include <string>

class Scene;
class Animation;
class Game
{

	std::map<std::string, std::shared_ptr<Scene> > m_scenes{};
	std::string m_currentScene;

	void update(sf::Time l_dt);
	void render(sf::RenderWindow& l_wnd);

public:
	sf::RenderWindow wnd;
	bool paused{ false };
	static bool gameRunning;

	// cuz im an explicit mofukka
	explicit Game();
	~Game() = default;
	// child safety deletes.  Can't move it, cant copy it.  Cuz it's the fucking game, doi.  
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&) = delete;
	Game& operator=(Game&&) = delete;

	//  One function to rule them all
	void mainLoop();
	void changeScene(std::string l_scene);
	std::shared_ptr<Scene> currentScene();

};
#endif