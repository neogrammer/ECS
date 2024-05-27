#include "Factories.hpp"
#include "../core/Config.hpp"

std::shared_ptr<Entity> Make::Player(size_t id)
{
	auto e = std::shared_ptr<Entity>(new Entity("player", { {0,0},{84,84} }, id, "Player", Vec2(400.f, 300.f)));
	e->addComponent<CGravity>(Vec2(0,1) , 19.8f);
	return e;
}

std::shared_ptr<Entity> Make::Tile(size_t id, std::string texName, sf::IntRect texRect, Vec2 pos, bool solid)
{

	auto e = std::shared_ptr<Entity>(new Entity("tile", { {texRect.left,texRect.top},{texRect.width,texRect.height} }, id, texName, pos));

	return e;
}