#ifndef ENTITY_HPP__
#define ENTITY_HPP__
#include <utility>
#include <memory>
#include <string>
#include "component/components/Components.hpp"

class Entity
{
	friend class EntityManager;

	const size_t m_id{ 0 };
	const std::string m_tag{ "default" };
	Entity() {}

public:
	std::shared_ptr<CTransform> cTransform{};
	
};
#endif