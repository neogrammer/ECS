#ifndef COLLISIONSYSTEM_HPP__
#define COLLISIONSYSTEM_HPP__

#include <system/System.hpp>
#include <SFML/Graphics.hpp>
#include <gamestate/gamestates/PlayState.hpp>

class CollisionSystem : public System
{
	GameState& gameState;

public:

	CollisionSystem(PlayState& l_gameState, sf::RenderWindow& l_wnd, sf::Time& l_dt);
	~CollisionSystem() override final;

	void update();

	// not used on this system
	void draw();
};

#endif