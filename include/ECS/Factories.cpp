#include "Factories.hpp"
#include "../core/Config.hpp"

std::shared_ptr<Entity> Make::Player(size_t id)
{
	auto e = std::shared_ptr<Entity>(new Entity("player", { {0,0},{84,84} }, id, "Player", Vec2(400.f, 300.f)));
	e->addComponent<cGravity>(Vec2(0,1) , 19.8f);
	e->addComponent<cRigidBody>(true, Vec2(84,84), Vec2(0,0), Vec2(400.f,300.f));
	e->addComponent<cAnimation>();
	cAnimation::setup(*e, "assets/data/animations/player.anim");
	cAnimation::changeAnimation(*e, "JumpRight");
	return e;
}

std::shared_ptr<Entity> Make::Tile(size_t id, std::string texName, sf::IntRect texRect, Vec2 pos, bool solid)
{

	auto e = std::shared_ptr<Entity>(new Entity("tile", { {texRect.left,texRect.top},{texRect.width,texRect.height} }, id, texName, pos));
	e->addComponent<cRigidBody>(false, Vec2(texRect.width,texRect.height), Vec2(0, 0), Vec2(pos.x, pos.y));
	e->cMgr.setOrigin({ 0.f, 0.f });

	return e;
}