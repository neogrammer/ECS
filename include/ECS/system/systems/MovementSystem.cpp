#include "MovementSystem.hpp"
#include "../core/GameEngine.hpp"
#include "../scene/scenes/Play.hpp"


MovementSystem::MovementSystem(GameEngine& l_game)
	: System{l_game}
{

}

MovementSystem::~MovementSystem()
{
}

void MovementSystem::update(double l_dt)
{
	if (dynamic_cast<Play*>(game.currentScene().get()))
	{
		auto player = game.currentScene()->eMgr().getEntity((size_t)0);
		player->cShape->sprite.move({(float)(player->cTransform->velocity.x * l_dt), (float)(player->cTransform->velocity.y * l_dt)});
		player->cTransform->prevPos = player->cTransform->pos;
		player->cTransform->pos = { player->cShape->sprite.getPosition().x, player->cShape->sprite.getPosition().y };
	}
}