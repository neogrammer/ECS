#include "Factories.hpp"
#include "../core/Config.hpp"
std::shared_ptr<Entity> Make::Player(EntityManager& l_eMgr, size_t id)
{
	auto e = std::shared_ptr<Entity>(new Entity(l_eMgr, "player", { {0,0},{84,84} }, id, "Player", Vec2(400.f, 300.f)));
	e->addComponent<cGravity>(Vec2(0,1) , 19.8f);
	e->addComponent<cRigidBody>(true, Vec2(84,84), Vec2(0,0), Vec2(400.f,300.f));
	e->addComponent<cAnimation>();
	cAnimation::setup(*e, "assets/data/animations/player.anim");
	cAnimation::changeAnimation(*e, "JumpRight");
	e->addComponent<cPlayerStatus>();
	e->getComponent<cPlayerStatus>().isfacingLeft = false;
	e->getComponent<cPlayerStatus>().isFalling = true;

	return e;
}
