#ifndef PLAYSTATE_HPP__
#define PLAYSTATE_HPP__
#include "../GameState.hpp"
#include <string>
#include "../../core/Config.hpp"
#include "../../level/Tilemap.hpp"
class InputSystem;
class Player;

class PlayState : public GameState
{
	std::shared_ptr<InputSystem> inputSystem;



public:
	std::shared_ptr<Player> the_player;

	std::shared_ptr<Tilemap> tmap;

	PlayState(Game& l_game, ActionMap<int>& l_actionMap, std::string l_playerCfgFile);
	~PlayState() override final;
	void init() override final;
	void processInput() override final;
	void processEvents(std::vector<sf::Event>& l_evts) override final;
	void update(double l_dt) override final;
	void render(sf::RenderWindow& l_wnd) override final;


};
#endif