#ifndef GAMEENGINE_HPP__
#define GAMEENGINE_HPP__
#include <vector>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <map>
#include <memory>
#include <utility>
#include <string>

class Scene;

struct GameProperties
{
	static constexpr double FPS = 0.016666667;
	static constexpr int SCRW = 1024;
	static constexpr int SCRH = 576;
};

class GameEngine
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
	explicit GameEngine();
	~GameEngine() = default;
	// child safety deletes.  Can't move it, cant copy it.  Cuz it's the fucking game, doi.  
	GameEngine(const GameEngine&) = delete;
	GameEngine& operator=(const GameEngine&) = delete;
	GameEngine(GameEngine&&) = delete;
	GameEngine& operator=(GameEngine&&) = delete;

	//  One function to rule them all
	void mainLoop();
	void changeScene(std::string l_scene);
	std::shared_ptr<Scene> currentScene();

};

#endif