#ifndef RENDERSYSTEM_HPP__
#define RENDERSYSTEM_HPP__

#include "../System.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
class GameEngine;

class RenderSystem : public System
{
	sf::RenderWindow* p_wnd{ nullptr };
public:
	RenderSystem(GameEngine& l_game, sf::RenderWindow* l_wnd);
	~RenderSystem() override final;

	void update(double l_dt) override final;

	void render();
};

#endif