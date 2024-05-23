#ifndef ENTITY_HPP__
#define ENTITY_HPP__
#include <utility>
#include <memory>
#include <string>
#include "component/components/Components.hpp"

class Entity
{
	friend class EntityManager;

	size_t m_id{ 0 };
	std::string m_tag{ "default" };
	bool m_dead{ false };	

public:
	std::shared_ptr<CTransform> cTransform{};
	
	Entity(const std::string& l_tag, size_t l_id);

	void destroy();
};
#endif