#include "RenderSystem.hpp"
#include "../core/GameEngine.hpp"


RenderSystem::RenderSystem(GameEngine& l_game, sf::RenderWindow* l_wnd)
	: System{l_game}
	, p_wnd{l_wnd}
{
}

RenderSystem::~RenderSystem()
{
	// non-owner
	p_wnd = nullptr;
}


void RenderSystem::update(double l_dt)
{

	// for readability
	render();

}

void RenderSystem::render()
{
	game.player().cShape->shape.setPosition({ game.player().cTransform->pos.x, game.player().cTransform->pos.y });
	p_wnd->draw(game.player().cShape->shape);

	
}