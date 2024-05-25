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
		auto& s = player->getComponent<CShape>();
		auto& t = player->getComponent<CTransform>();

		s.sprite.move({(float)(t.velocity.x * l_dt), (float)(t.velocity.y * l_dt)});
		t.prevPos = t.pos;
		t.pos = { s.sprite.getPosition().x, s.sprite.getPosition().y };
	}
}