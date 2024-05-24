#ifndef TITLE_HPP__
#define TITLE_HPP__
#include "../Scene.hpp"
#include "../../core/Config.hpp"
class System;
class Title : public Scene
{
	std::vector<std::unique_ptr<System> > m_systems;

	sf::Sprite titleBG;
	sf::Text titleFont;
	sf::Text level1Text;
	sf::Sprite selector;
	sf::Sprite spear;

	

public:
	Title(GameEngine& l_game);
	~Title() override final;

	void propogateInput(std::vector<sf::Event> l_evts) override final;
	void processEvents(std::vector<sf::Event>& l_evts) override final;
	void update(double l_dt) override final;
	void render(sf::RenderWindow& l_wnd) override final;
};
#endif