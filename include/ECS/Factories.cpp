#include "Factories.hpp"
#include "../core/Config.hpp"

std::shared_ptr<Entity> Make::Player(size_t id)
{
	auto e = std::make_shared<Entity>(Entity{ "player", id });

	e->addComponent<CTransform>(Vec2(512, 288), Vec2(0.f, 0.f));
	e->addComponent<CShape>(&Config::textures.get((int)Config::Textures::Player), Vec2(84, 84), Vec2(42, 42));
	e->addComponent<CGravity>(Vec2(0,1) , 19.8f);
	e->addComponent<CBBox>(42,42, Vec2(84, 84));
	return e;
}

std::shared_ptr<Entity> Make::Tile(size_t id, std::string texName, sf::IntRect texRect, Vec2 pos, bool solid)
{


	auto e = std::make_shared<Entity>(Entity{ "tile", id });

	e->addComponent<CTransform>(Vec2(pos.x, pos.y), Vec2(0,0));
	e->addComponent<CShape>(&Config::textures.get((int)Config::Textures::Tileset1), Vec2(texRect.width, texRect.height), Vec2(texRect.width / 2.f, texRect.height / 2.f), Vec2(texRect.left, texRect.top));
	e->addComponent<CBBox>(texRect.width / 2.f, texRect.height / 2.f, Vec2(texRect.width, texRect.height));
	e->getComponent<CBBox>().solid = solid;

	return e;
}