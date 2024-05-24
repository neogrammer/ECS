#include "Factories.hpp"

std::shared_ptr<Entity> Make::Player(size_t id)
{
	auto e = std::make_shared<Entity>(Entity{ "player", id });

	e->cName = std::make_shared<CName>("Cid");
	e->cTransform = std::make_shared<CTransform>(Vec2(512, 288), Vec2(0.f, 0.f));
	e->cShape = std::make_shared<CShape>(Vec2(10, 10), 7, 3, 255, 0, 0, 255, 255, 255, 20);

	return e;
};