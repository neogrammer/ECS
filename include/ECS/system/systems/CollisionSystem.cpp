#include "CollisionSystem.hpp"
#include "../core/GameEngine.hpp"
#include "../scene/scenes/Play.hpp"
#include "../util/Physics.hpp"

CollisionSystem::CollisionSystem(GameEngine& l_game)
	: System{l_game}
{
}

CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::update(double l_dt)
{
	if (dynamic_cast<Play*>(game.currentScene().get()))
	{
		auto player = game.currentScene()->eMgr().getEntity((size_t)0);
		player->getComponent<CTransform>().velocity.y += player->getComponent<CGravity>().magnitude * (float)l_dt;
		auto& eVec = dynamic_cast<Play*>(game.currentScene().get())->tmap->getTiles();
		Physics::resolveCollisions(player, eVec);

	}
}