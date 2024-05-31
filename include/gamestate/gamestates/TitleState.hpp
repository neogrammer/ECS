#ifndef TITLESTATE_HPP__
#define TITLESTATE_HPP__
#include "../GameState.hpp"
#include "../../core/Config.hpp"
#include <array>


class TitleState : public GameState
{

	sf::Sprite titleBG;
	sf::Text titleFont;
	sf::Text level1Text;
	sf::Sprite selector;
	sf::Sprite spear;

	//std::shared_ptr<InputSystem> inputSystem;


	const std::array<sf::Vector2f, 2> choicePos{
		{{420.f,80.f},
		{320.f,160.f}}
	};
	size_t curChoice{};

public:
	TitleState(Game& l_game, ActionMap<int>& l_actionMap);
	~TitleState() override final;
	void init() override final;
	void processInput() override final;
	void processEvents(std::vector<sf::Event>& l_evts) override final;
	void update(double l_dt) override final;
	void render(sf::RenderWindow& l_wnd) override final;
};
#endif