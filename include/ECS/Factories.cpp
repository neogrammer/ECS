#include "Factories.hpp"
#include "../core/Config.hpp"

std::shared_ptr<Entity> Make::Player(size_t id)
{
	auto e = std::make_shared<Entity>(Entity{ "player", id });

	e->cName = std::make_shared<CName>("Cid");
	e->cTransform = std::make_shared<CTransform>(Vec2(512, 288), Vec2(0.f, 0.f));
	e->cShape = std::make_shared<CShape>(&Config::textures.get((int)Config::Textures::Player), Vec2(84, 84), Vec2(42, 42));

	return e;
};