#ifndef ENTITY_HPP__
#define ENTITY_HPP__
#include <utility>
#include <memory>
#include <string>
#include "component/components/Components.hpp"
#include <tuple>

typedef std::tuple<
	CTransform,
	CGravity,
	CLifespan,
	CBBox,
	CShape,
	CAnimation
> CTuple;



class Entity
{
	friend class EntityManager;
	friend class Make;

	size_t m_id{ 0 };
	std::string m_tag{ "default" };
	bool m_alive{ true };
	std::tuple<CTransform, CGravity, CLifespan, CBBox, CShape, CAnimation> m_cTuple;

	Entity(const std::string& l_tag, size_t l_id);
public:

	size_t id() const;
	bool isAlive() const;
	const std::string& tag();
	void destroy();

	template <typename AComponent>
	bool hasComponent() const
	{
		return getComponent<AComponent>().has;
	};

	template <typename AComponent, typename... AComponentArgs>
	AComponent& addComponent(AComponentArgs&&... l_args)
	{
		auto& component = getComponent<AComponent>();
		component = AComponent(std::forward<AComponentArgs>(l_args)...);
		component.has = true;
		return component;
	};

	template <typename AComponent>
	AComponent & getComponent()
	{
		return std::get<AComponent>(m_cTuple);
	};

	template <typename AComponent>
	const AComponent& getComponent() const
	{
		return std::get<AComponent>(m_cTuple);
	};

	template <typename AComponent>
	void removeComponent()
	{
		getComponent<AComponent>() = AComponent();
	};

};
#endif