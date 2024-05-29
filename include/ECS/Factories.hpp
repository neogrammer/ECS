#ifndef FACTORIES_HPP__
#define FACTORIES_HPP__

#include "Entity.hpp"
class EntityManager;
class Make
{
	friend class EntityManager;

	Make() {}

	static std::shared_ptr<Entity> Player(EntityManager& l_eMgr, size_t id);
	

public:
	virtual ~Make() = 0;

};

#endif