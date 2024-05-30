#ifndef TITLE_HPP__
#define TITLE_HPP__
#include "../Scene.hpp"
#include "../../core/Config.hpp"
#include <array>

class InputSystem;
class CollisionSystem;
class MovementSystem;
class RenderSystem;

class Title : public Scene
{

	sf::Sprite titleBG;
	sf::Text titleFont;
	sf::Text level1Text;
	sf::Sprite selector;
	sf::Sprite spear;

	std::shared_ptr<InputSystem> inputSystem;


	const std::array<sf::Vector2f, 2> choicePos{
		{{420.f,80.f},
		{320.f,160.f}}
	};
	size_t curChoice{};

public:
	Title(GameEngine& l_game, ActionMap<int>& l_actionMap);
	~Title() override final;
	void init() override final;
	void processInput() override final;
	void processEvents(std::vector<sf::Event>& l_evts) override final;
	void update(double l_dt) override final;
	void render(sf::RenderWindow& l_wnd) override final;
};
#endif