#ifndef PLAY_HPP__
#define PLAY_HPP__
#include "../Scene.hpp"
#include <string>
#include "../../core/Config.hpp"
class System;
class Play : public Scene
{
	std::string m_levelPath;
	std::shared_ptr<Entity> m_player{};
	PlayerConfig m_playerCfg;

	std::vector<std::unique_ptr<System> > m_systems;

public:


	Play(GameEngine& l_game, ActionMap<int>& l_actionMap, std::string l_playerCfgFile);
	~Play() override final;

	void processInput() override final;
	void processEvents(std::vector<sf::Event>& l_evts) override final;
	void update(double l_dt) override final;
	void render(sf::RenderWindow& l_wnd) override final;

	std::shared_ptr<Entity> player();
};
#endif