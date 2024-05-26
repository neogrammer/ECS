#ifndef FACTORIES_HPP__
#define FACTORIES_HPP__

#include "Entity.hpp"

class Make
{
	friend class EntityManager;

	Make() {}

	static std::shared_ptr<Entity> Player(size_t id);
	

public:
	virtual ~Make() = 0;

	static std::shared_ptr<Entity> Tile(size_t id, std::string texName, sf::IntRect texRect, Vec2 pos, bool solid = true);

};

#endif