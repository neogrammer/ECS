#ifndef PLAYSTATE_HPP__
#define PLAYSTATE_HPP__
#include "../GameState.hpp"
#include <string>
#include "../../core/Config.hpp"
#include "../../level/Tilemap.hpp"
#include <gameObj/actors/PlayerObj.hpp>
class Player;

class PlayState : public GameState
{
	PlayerObj player;

public:
	PlayState(Game& l_game, ActionMap<int>& l_actionMap);
	~PlayState() override final;
	void init() override final;
	void processInput() override final;
	void processEvents(std::vector<sf::Event>& l_evts) override final;
	void update(double l_dt) override final;
	void render(sf::RenderWindow& l_wnd) override final;


};
#endif