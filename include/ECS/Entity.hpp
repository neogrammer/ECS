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
	bool m_alive{ true };	

	Entity(const std::string& l_tag, size_t l_id);
public:
	std::shared_ptr<CTransform> cTransform{};
	std::shared_ptr<CName> cName{};
	std::shared_ptr<CShape> cShape{};
	std::shared_ptr<CBBox> cBBox{};

	
	
	const std::string& tag();
	void destroy();
};
#endif