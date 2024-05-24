#include "RenderSystem.hpp"
#include "../core/GameEngine.hpp"
#include "../scene/scenes/Play.hpp"
#include "../scene/scenes/Title.hpp"


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
	if (dynamic_cast<Play*>(game.currentScene().get()))
	{
		auto scene = dynamic_cast<Play*>(game.currentScene().get());
		scene->player()->cShape->sprite.setPosition({ scene->player()->cTransform->pos.x, scene->player()->cTransform->pos.y });
		p_wnd->draw(scene->player()->cShape->sprite);
	}
	else if (dynamic_cast<Title*>(game.currentScene().get()))
	{ 
		auto scene = dynamic_cast<Title*>(game.currentScene().get());
		// draw title screen
	}
	else
	{

	}

	
}