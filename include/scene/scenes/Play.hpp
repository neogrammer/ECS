#ifndef PLAY_HPP__
#define PLAY_HPP__
#include "../Scene.hpp"
#include <string>
#include "../../core/Config.hpp"
#include "../../level/Tilemap.hpp"
class InputSystem;
class CollisionSystem;
class MovementSystem;
class RenderSystem;
class Player;

class Play : public Scene
{
	std::string m_levelPath;
	PlayerConfig m_playerCfg;


	std::shared_ptr<CollisionSystem> collisionSystem;
	std::shared_ptr<InputSystem> inputSystem;
	std::shared_ptr<MovementSystem> movementSystem;
	std::shared_ptr<RenderSystem> renderSystem;
	

public:
	std::shared_ptr<Player> the_player;

	std::shared_ptr<Tilemap> tmap;

	Play(GameEngine& l_game, ActionMap<int>& l_actionMap, std::string l_playerCfgFile);
	~Play() override final;
	void init() override final;
	void processInput() override final;
	void processEvents(std::vector<sf::Event>& l_evts) override final;
	void update(double l_dt) override final;
	void render(sf::RenderWindow& l_wnd) override final;

	std::shared_ptr<Entity> player();
};
#endif